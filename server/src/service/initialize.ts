import type { InitializeParams, InitializeResult } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { CodeActionKind, TextDocumentSyncKind } from 'vscode-languageserver/node';
import { serverStore } from './store';

export function setupOnInitialize(connection: ServerConnection): void {
  connection.onInitialize(({ capabilities }: InitializeParams) => {
    serverStore.setWorkspaceFolderCapability(!!(capabilities.workspace && !!capabilities.workspace.workspaceFolders));

    serverStore.setDiagnosticRelatedInformationCapability(!!(
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
    if (serverStore.hasWorkspaceFolders()) {
      result.capabilities.workspace = {
        workspaceFolders: {
          supported: true,
        },
      };
    }
    return result;
  });
}
