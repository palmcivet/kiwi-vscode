import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { Location, ReferenceParams, TextDocuments } from 'vscode-languageserver/node';
import type { FilePosition } from '../parser';
import type { Schema } from '../parser/schema';
import type { ServerConnection } from './util';
import { isInsideRange } from '../helper';
import { convertPosition, fileUriToPath, pathToFileUri, readKiwiFile } from '../parser';
import { getSchema, loadIncludedSchemas } from './util';

export function setupOnReference(connection: ServerConnection, documents: TextDocuments<TextDocument>): void {
  connection.onReferences(
    (params: ReferenceParams): Location[] => {
      const document = documents.get(params.textDocument.uri);
      if (!document) {
        return [];
      }

      const filePath = fileUriToPath(document.uri);
      connection.console.log(`Finding references in ${filePath} at position ${params.position.line}:${params.position.character}`);

      // 获取当前文件及其所有依赖的 Schema
      const allSchemas = new Map<string, Schema>();
      const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

      // 首先加载当前文件
      const currentFileContent = readKiwiFile(filePath);
      fileContents.set(filePath, currentFileContent);
      const schema = getSchema(params.textDocument.uri, documents);
      if (!schema) {
        return [];
      }
      allSchemas.set(filePath, schema);

      // 加载所有依赖文件
      const includedSchemas = loadIncludedSchemas(filePath);
      for (const [path, schema] of includedSchemas) {
        allSchemas.set(path, schema);
        const content = readKiwiFile(path);
        fileContents.set(path, content);
      }

      connection.console.log(`Loaded ${allSchemas.size} schemas for reference search`);

      // 找到点击位置的定义
      let targetName: string | undefined;
      let targetLoc: Location | undefined;

      // 检查是否点击在定义名称上
      for (const def of schema.definitions) {
        if (isInsideRange(params.position, def.nameSpan)) {
          targetName = def.name;
          targetLoc = {
            uri: params.textDocument.uri,
            range: def.nameSpan,
          };
          break;
        }

        // 检查是否点击在字段类型上
        if (def.kind !== 'ENUM' && isInsideRange(params.position, def.fieldsSpan)) {
          for (const field of def.fields) {
            if (field.typeSpan && isInsideRange(params.position, field.typeSpan)) {
              targetName = field.type;
              targetLoc = {
                uri: params.textDocument.uri,
                range: field.typeSpan,
              };
              break;
            }
          }
          if (targetName)
            break;
        }
      }

      if (!targetName) {
        connection.console.log('No definition found at cursor position');
        return [];
      }

      connection.console.log(`Found definition ${targetName}, searching for references`);

      const references: Location[] = [];

      // 在所有文件中搜索引用
      for (const [path, schema] of allSchemas) {
        const fileContent = fileContents.get(path);
        if (!fileContent)
          continue;

        // 在定义中搜索引用
        for (const def of schema.definitions) {
          // 检查定义名称
          if (def.name === targetName) {
            references.push({
              uri: pathToFileUri(path),
              range: def.nameSpan,
            });
          }

          // 检查字段类型
          if (def.kind !== 'ENUM') {
            for (const field of def.fields) {
              if (field.type === targetName && field.typeSpan) {
                // 调整位置到原始文件
                const adjustedRange = {
                  start: {
                    line: convertPosition(field.typeSpan.start.line, path, fileContent.filePositions),
                    character: field.typeSpan.start.character,
                  },
                  end: {
                    line: convertPosition(field.typeSpan.end.line, path, fileContent.filePositions),
                    character: field.typeSpan.end.character,
                  },
                };

                references.push({
                  uri: pathToFileUri(path),
                  range: adjustedRange,
                });
              }
            }
          }
        }
      }

      // 如果需要包含声明，并且找到了目标位置
      if (params.context.includeDeclaration && targetLoc) {
        references.push(targetLoc);
      }

      connection.console.log(`Found ${references.length} references`);
      return references;
    },
  );
}
