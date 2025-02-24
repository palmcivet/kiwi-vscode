import type { FileStore } from '@server/store';
import type { ServerConnection } from './type';
import { KiwiFormatter } from '@server/formatter';
import { TextEdit } from 'vscode-languageserver/node';

export function setupOnFormatting(connection: ServerConnection, fileStore: FileStore): void {
  connection.onDocumentFormatting(({ textDocument }) => {
    const document = fileStore.getTextDocument(textDocument.uri);
    if (!document) {
      return null;
    }

    const formatter = new KiwiFormatter();
    const formattedText = formatter.format(document.getText());

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
