import type { Location, ReferenceParams } from 'vscode-languageserver/node';
import type { FilePosition, Schema } from '../parser';
import type { SchemaStore } from './store';
import type { ServerConnection } from './type';
import { isInsideRange } from '../helper';
import { convertPosition, fileUriToPath, pathToFileUri, readKiwiFile } from '../parser';

/**
 * Sets up the reference provider for the language server.
 * Handles requests to find all references of a symbol at a given position.
 * Supports finding references in both the current file and its dependencies.
 *
 * Key features:
 * 1. Finding references to type definitions
 * 2. Finding references to field types
 * 3. Supporting cross-file reference lookup
 *
 * @param connection - The server connection instance for communication
 * @param schemaStore - Store managing schema documents and their dependencies
 */
export function setupOnReference(connection: ServerConnection, schemaStore: SchemaStore): void {
  connection.onReferences(
    (params: ReferenceParams): Location[] => {
      const document = schemaStore.getTextDocument(params.textDocument.uri);
      if (!document) {
        return [];
      }

      const filePath = fileUriToPath(document.uri);
      connection.console.info(`Finding references in ${filePath} at position ${params.position.line}:${params.position.character}`);

      // Load schemas for the current file and all its dependencies
      const allSchemas = new Map<string, Schema>();
      const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

      // Load the current file's schema
      const currentFileContent = readKiwiFile(filePath);
      fileContents.set(filePath, currentFileContent);
      const schema = schemaStore.loadTextSchema(params.textDocument.uri);
      if (!schema) {
        return [];
      }
      allSchemas.set(filePath, schema);

      // Load all dependency files' schemas
      const includedSchemas = schemaStore.loadIncludedSchemas(filePath);
      for (const [path, schema] of includedSchemas) {
        allSchemas.set(path, schema);
        const content = readKiwiFile(path);
        fileContents.set(path, content);
      }

      connection.console.info(`Loaded ${allSchemas.size} schemas for reference search`);

      // Find the definition at the clicked position
      let targetName: string | undefined;
      let targetLoc: Location | undefined;

      // Check if clicked on a definition name
      for (const def of schema.definitions) {
        if (isInsideRange(params.position, def.nameSpan)) {
          targetName = def.name;
          targetLoc = {
            uri: params.textDocument.uri,
            range: def.nameSpan,
          };
          break;
        }

        // Check if clicked on a field type
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
        connection.console.error('No definition found at cursor position');
        return [];
      }

      connection.console.info(`Found definition ${targetName}, searching for references`);

      const references: Location[] = [];

      // Search for references across all files
      for (const [path, schema] of allSchemas) {
        const fileContent = fileContents.get(path);
        if (!fileContent)
          continue;

        // Search for references in definitions
        for (const def of schema.definitions) {
          // Check definition names
          if (def.name === targetName) {
            references.push({
              uri: pathToFileUri(path),
              range: def.nameSpan,
            });
          }

          // Check field types
          if (def.kind !== 'ENUM') {
            for (const field of def.fields) {
              if (field.type === targetName && field.typeSpan) {
                // Adjust position to original file coordinates
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

      // Include the declaration if requested and found
      if (params.context.includeDeclaration && targetLoc) {
        references.push(targetLoc);
      }

      connection.console.info(`Found ${references.length} references`);
      return references;
    },
  );
}
