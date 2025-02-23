import type { InitializeParams, InitializeResult } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { configStore } from '@server/store';
import { CodeActionKind, TextDocumentSyncKind } from 'vscode-languageserver/node';

export function setupOnInitialize(connection: ServerConnection): void {
  connection.onInitialize(({ capabilities, initializationOptions }: InitializeParams) => {
    configStore.setWorkspaceFolderCapability(!!(capabilities.workspace && !!capabilities.workspace.workspaceFolders));

    configStore.setDiagnosticRelatedInformationCapability(!!(capabilities.textDocument
      && capabilities.textDocument.publishDiagnostics
      && capabilities.textDocument.publishDiagnostics.relatedInformation));

    configStore.setEnableWarningDiagnostics(!!(initializationOptions?.enableWarningDiagnostics));

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

  connection.onDidChangeConfiguration(({ settings }) => {
    configStore.setEnableWarningDiagnostics(!!(settings?.enableWarningDiagnostics));
  });
}
