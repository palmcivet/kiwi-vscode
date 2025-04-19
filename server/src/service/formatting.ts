import type { FileStore } from '@server/store';
import type { ServerConnection } from './type';
import { TextEdit } from 'vscode-languageserver/node';

export function setupOnFormatting(connection: ServerConnection, fileStore: FileStore): void {
  connection.onDocumentFormatting(async ({ textDocument }) => {
    const document = fileStore.getTextDocument(textDocument.uri);
    if (!document) {
      return null;
    }

    const formattedText = document.getText();

    return [
      TextEdit.replace(
        {
          start: { line: 0, character: 0 },
          end: { line: document.lineCount, character: 0 },
        },
        formattedText,
      ),
    ];
  });
}
