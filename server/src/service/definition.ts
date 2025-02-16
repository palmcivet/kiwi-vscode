import type { Definition, DefinitionParams, Position, Range } from 'vscode-languageserver/node';
import type { FilePosition, Schema } from '../parser';
import type { SchemaStore } from './store';
import type { ServerConnection } from './type';
import { dirname, resolve } from 'node:path';
import { convertPosition, fileUriToPath, parseIncludes, pathToFileUri, readKiwiFile } from '../parser';

// Helper functions
function isPositionInRange(position: Position, range: Range): boolean {
  if (position.line !== range.start.line)
    return false;
  return position.character >= range.start.character
    && position.character <= range.end.character;
}

export function setupOnDefinition(connection: ServerConnection, schemaStore: SchemaStore): void {
  connection.onDefinition((params: DefinitionParams): Definition | null => {
    const document = schemaStore.getTextDocument(params.textDocument.uri);
    if (!document) {
      return null;
    }

    const filePath = fileUriToPath(document.uri);
    connection.console.log(`Finding definition in ${filePath} at position ${params.position.line}:${params.position.character}`);

    // 首先检查是否点击的是 include 路径
    const text = document.getText();
    const includes = parseIncludes(text);
    for (const include of includes) {
      if (isPositionInRange(params.position, include.pathRange)) {
        const currentDir = dirname(filePath);
        const targetPath = resolve(currentDir, include.path);
        return {
          uri: pathToFileUri(targetPath),
          range: { start: { line: 0, character: 0 }, end: { line: 0, character: 0 } },
        };
      }
    }

    // 获取当前文件及其所有依赖的 Schema
    const allSchemas = new Map<string, Schema>();
    const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

    // 加载当前文件
    const currentFileContent = readKiwiFile(filePath);
    fileContents.set(filePath, currentFileContent);
    const schema = schemaStore.loadTextSchema(params.textDocument.uri);
    if (!schema) {
      return null;
    }
    allSchemas.set(filePath, schema);

    // 加载所有依赖文件
    const includedSchemas = schemaStore.loadIncludedSchemas(filePath);
    for (const [path, schema] of includedSchemas) {
      allSchemas.set(path, schema);
      const content = readKiwiFile(path);
      fileContents.set(path, content);
    }

    connection.console.log(`Loaded ${allSchemas.size} schemas for definition lookup`);

    // 在当前文件中查找点击的类型
    let targetType: string | undefined;

    // 检查是否点击在字段类型上
    for (const def of schema.definitions) {
      if (def.kind !== 'ENUM') {
        for (const field of def.fields) {
          if (field.typeSpan && isPositionInRange(params.position, field.typeSpan)) {
            targetType = field.type;
            break;
          }
        }
        if (targetType)
          break;
      }
    }

    if (!targetType) {
      connection.console.log('No type found at cursor position');
      return null;
    }

    connection.console.log(`Looking for definition of type ${targetType}`);

    // 在所有文件中查找类型定义
    for (const [path, schema] of allSchemas) {
      const fileContent = fileContents.get(path);
      if (!fileContent)
        continue;

      for (const def of schema.definitions) {
        if (def.name === targetType) {
          // 调整位置到原始文件
          const adjustedRange = {
            start: {
              line: convertPosition(def.nameSpan.start.line, path, fileContent.filePositions),
              character: def.nameSpan.start.character,
            },
            end: {
              line: convertPosition(def.nameSpan.end.line, path, fileContent.filePositions),
              character: def.nameSpan.end.character,
            },
          };

          connection.console.log(`Found definition in ${path} at line ${adjustedRange.start.line}`);
          return {
            uri: pathToFileUri(path),
            range: adjustedRange,
          };
        }
      }
    }

    connection.console.log('Definition not found');
    return null;
  });
}
