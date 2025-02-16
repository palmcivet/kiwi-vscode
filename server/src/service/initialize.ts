import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { InitializeParams, InitializeResult, TextDocuments } from 'vscode-languageserver/node';
import type { ServerConnection } from './util';
import { CodeActionKind, TextDocumentSyncKind } from 'vscode-languageserver/node';
import { store } from './store';

export function setupOnInitialize(connection: ServerConnection, _documents: TextDocuments<TextDocument>): void {
  connection.onInitialize(({ capabilities }: InitializeParams) => {
    store.setWorkspaceFolderCapability(!!(capabilities.workspace && !!capabilities.workspace.workspaceFolders));

    store.setDiagnosticRelatedInformationCapability(!!(
      capabilities.textDocument
      && capabilities.textDocument.publishDiagnostics
      && capabilities.textDocument.publishDiagnostics.relatedInformation
    ));

    const result: InitializeResult = {
      capabilities: {
        textDocumentSync: TextDocumentSyncKind.Incremental,
        completionProvider: {},
        diagnosticProvider: {
          interFileDependencies: false,
          workspaceDiagnostics: false,
        },
        hoverProvider: true,
        definitionProvider: true,
        referencesProvider: true,
        documentSymbolProvider: true,
        codeActionProvider: {
          codeActionKinds: [CodeActionKind.QuickFix],
          resolveProvider: true,
        },
      },
    };
    if (store.hasWorkspaceFolders()) {
      result.capabilities.workspace = {
        workspaceFolders: {
          supported: true,
        },
      };
    }
    return result;
  });
}
