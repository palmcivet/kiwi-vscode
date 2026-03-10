import type { FileStore } from '@server/store';
import type { ServerConnection } from './type';
import { TextEdit } from 'vscode-languageserver/node';
import { format } from '@server/formatter';

export function setupOnFormatting(
  connection: ServerConnection,
  fileStore: FileStore,
): void {
  connection.onDocumentFormatting(async ({ textDocument }) => {
    const document = fileStore.getTextDocument(textDocument.uri);
    if (!document) {
      return null;
    }

    try {
      const formattedText = await format(document.getText());

      return [
        TextEdit.replace(
          {
            start: { line: 0, character: 0 },
            end: { line: document.lineCount, character: 0 },
          },
          formattedText,
        ),
      ];
    } catch {
      return null;
    }
  });
}
