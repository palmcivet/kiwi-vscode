import type { Definition, DefinitionParams } from 'vscode-languageserver/node';
import type { FilePosition, Schema } from '../parser';
import type { SchemaStore } from './store';
import type { ServerConnection } from './type';
import { dirname, resolve } from 'node:path';
import { isPositionInRange } from '../helper';
import {
  convertPosition,
  fileUriToPath,
  parseIncludes,
  pathToFileUri,
  readKiwiFile,
} from '../parser';

/**
 * Sets up the definition provider for the language server.
 * Handles requests to find the definition of a symbol at a given position.
 * Supports two main features:
 * 1. Finding the target file for \@include directives
 * 2. Finding type definitions in the current file and its dependencies
 *
 * @param connection - The server connection instance for communication
 * @param schemaStore - Store managing schema documents and their dependencies
 */
export function setupOnDefinition(connection: ServerConnection, schemaStore: SchemaStore): void {
  connection.onDefinition((params: DefinitionParams): Definition | null => {
    const document = schemaStore.getTextDocument(params.textDocument.uri);
    if (!document) {
      return null;
    }

    const filePath = fileUriToPath(document.uri);
    connection.console.debug(`Finding definition in ${filePath} at position ${params.position.line}:${params.position.character}`);

    // First, check if the cursor is on an include path
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

    // Get schemas for the current file and all its dependencies
    const allSchemas = new Map<string, Schema>();
    const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

    // Load the current file's schema
    const currentFileContent = readKiwiFile(filePath);
    fileContents.set(filePath, currentFileContent);
    const schema = schemaStore.loadTextSchema(params.textDocument.uri);
    if (!schema) {
      return null;
    }
    allSchemas.set(filePath, schema);

    // Load all dependency files' schemas
    const includedSchemas = schemaStore.loadIncludedSchemas(filePath);
    for (const [path, schema] of includedSchemas) {
      allSchemas.set(path, schema);
      const content = readKiwiFile(path);
      fileContents.set(path, content);
    }

    connection.console.info(`Loaded ${allSchemas.size} schemas for definition lookup`);

    // Find the type that was clicked in the current file
    let targetType: string | undefined;

    // Check if the cursor is on a field type
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
      connection.console.error('No type found at cursor position');
      return null;
    }

    connection.console.info(`Looking for definition of type ${targetType}`);

    // Search for the type definition across all files
    for (const [path, schema] of allSchemas) {
      const fileContent = fileContents.get(path);
      if (!fileContent)
        continue;

      for (const def of schema.definitions) {
        if (def.name === targetType) {
          // Adjust the position to the original file's coordinates
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

          connection.console.info(`Found definition in ${path} at line ${adjustedRange.start.line}`);
          return {
            uri: pathToFileUri(path),
            range: adjustedRange,
          };
        }
      }
    }

    connection.console.error('Definition not found');
    return null;
  });
}
