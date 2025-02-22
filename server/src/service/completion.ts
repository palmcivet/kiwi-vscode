import type { Schema } from '@server/parser';
import type { FileStore } from '@server/store';
import type { CompletionItem, TextDocumentPositionParams } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { fileUriToPath, NativeTypes } from '@server/parser';
import { CompletionItemKind } from 'vscode-languageserver/node';

/**
 * Sets up completion provider for the language server.
 * Handles code completion requests and provides relevant suggestions based on context.
 *
 * @param connection - The server connection instance for communication
 * @param fileStore - Store managing schema documents and their dependencies
 */
export function setupOnCompletion(connection: ServerConnection, fileStore: FileStore): void {
  connection.onCompletion(
    (textDocumentPosition: TextDocumentPositionParams): CompletionItem[] => {
      const document = fileStore.getTextDocument(textDocumentPosition.textDocument.uri);
      if (!document) {
        return [];
      }

      const filePath = fileUriToPath(document.uri);
      connection.console.debug(`Computing completions for ${filePath} at line ${textDocumentPosition.position.line}`);

      // Load current file's schema and its dependencies
      const allSchemas = new Map<string, Schema>();

      // Load schema for current file
      const schema = fileStore.loadTextSchema(textDocumentPosition.textDocument.uri);
      if (!schema) {
        connection.console.error(`No schema found for ${filePath}`);
        return [];
      }
      allSchemas.set(filePath, schema);

      // Load schemas from all included files
      const includedSchemas = fileStore.loadIncludedSchemas(filePath);
      for (const [path, schema] of includedSchemas) {
        allSchemas.set(path, schema);
      }

      // Collect all available types for completion
      const typeCompletions: CompletionItem[] = [
        // Add built-in types
        ...NativeTypes.map(ty => ({
          label: ty,
          kind: CompletionItemKind.Field,
          detail: '(builtin type)',
        })),
        // Add user-defined types from all schemas
        ...Array.from(allSchemas.values()).flatMap(schema =>
          schema.definitions.map(d => ({
            label: d.name,
            kind: d.kind === 'ENUM'
              ? CompletionItemKind.Enum
              : d.kind === 'STRUCT'
                ? CompletionItemKind.Interface
                : CompletionItemKind.Class,
            detail: `(${d.kind.toLowerCase()} from ${schema === allSchemas.get(filePath) ? 'current file' : 'imported file'})`,
          })),
        ),
      ];

      // Define top-level declarations available for completion
      const toplevelCompletions = ['message ', 'struct ', 'enum '].map(kw => ({
        label: kw,
        kind: CompletionItemKind.Keyword,
        detail: '(declaration)',
      }));

      // Get current line text and cursor position
      const lines = document.getText().split('\n');
      const currentLine = lines[textDocumentPosition.position.line];
      const currentCharacter = textDocumentPosition.position.character;

      // Analyze current line context up to cursor position
      const linePrefix = currentLine.slice(0, currentCharacter).trim();

      // Handle empty lines - provide top-level completions
      if (!linePrefix) {
        // Add package declaration if not defined and cursor is at file start
        if (!schema.package && textDocumentPosition.position.line === 0) {
          toplevelCompletions.push({
            label: 'package ',
            kind: CompletionItemKind.Keyword,
            detail: '(declaration)',
          });
        }
        return toplevelCompletions;
      }

      // Check if cursor is inside a message definition
      const messageMatch = /^\s*message\s+\w+\s*\{/.test(currentLine);
      if (messageMatch) {
        return typeCompletions;
      }

      // Check if cursor is in a field definition
      const fieldMatch = /^\s*(\w+\s+)?(\w*)$/.exec(linePrefix);
      if (fieldMatch) {
        const [, typePart, _fieldPart] = fieldMatch;

        // If type is already entered, suggest field modifiers
        if (typePart) {
          return [{
            label: 'deprecated',
            kind: CompletionItemKind.Keyword,
            detail: '(field modifier)',
          }];
        }

        // Otherwise suggest available types
        return typeCompletions;
      }

      // Default to top-level completions
      return toplevelCompletions;
    },
  );
}
