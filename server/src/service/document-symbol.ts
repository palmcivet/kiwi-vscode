import type { FileStore } from '@server/store';
import type { DocumentSymbol, DocumentSymbolParams } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { SymbolKind } from 'vscode-languageserver/node';

export function setupOnDocumentSymbol(connection: ServerConnection, fileStore: FileStore): void {
  connection.onDocumentSymbol((params: DocumentSymbolParams): DocumentSymbol[] => {
    const schema = fileStore.loadTextSchema(params.textDocument.uri);

    if (!schema) {
      return [];
    }

    const symbols: DocumentSymbol[] = [];

    if (schema.package) {
      symbols.push({
        name: schema.package.text,
        kind: SymbolKind.Package,
        range: schema.package.span,
        selectionRange: schema.package.span,
      });
    }

    for (const def of schema.definitions) {
      symbols.push({
        name: def.name,
        kind: def.kind === 'ENUM' ? SymbolKind.Enum : SymbolKind.Class,
        range: def.defSpan,
        selectionRange: def.nameSpan,
      });

      for (const field of def.fields) {
        symbols.push({
          name: field.name,
          kind: def.kind === 'ENUM' ? SymbolKind.EnumMember : SymbolKind.Field,
          range: field.span,
          selectionRange: field.nameSpan,
        });
      }
    }

    return symbols;
  });
}
