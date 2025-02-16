import type { InitializeParams, InitializeResult } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { CodeActionKind, TextDocumentSyncKind } from 'vscode-languageserver/node';
import { configStore } from '../store';

export function setupOnInitialize(connection: ServerConnection): void {
  connection.onInitialize(({ capabilities }: InitializeParams) => {
    configStore.setWorkspaceFolderCapability(!!(capabilities.workspace && !!capabilities.workspace.workspaceFolders));

    configStore.setDiagnosticRelatedInformationCapability(!!(
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
    if (configStore.hasWorkspaceFolders()) {
      result.capabilities.workspace = {
        workspaceFolders: {
          supported: true,
        },
      };
    }
    return result;
  });
}
