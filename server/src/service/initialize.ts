import type { InitializeParams, InitializeResult } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { fileURLToPath } from 'node:url';
import { configStore } from '@server/store';
import { CodeActionKind, TextDocumentSyncKind } from 'vscode-languageserver/node';

export function setupOnInitialize(connection: ServerConnection): void {
  connection.onInitialize(({ capabilities, initializationOptions, workspaceFolders, rootUri }: InitializeParams) => {
    configStore.setWorkspaceFolderCapability(!!(capabilities.workspace && !!capabilities.workspace.workspaceFolders));

    // Extract workspace root path from LSP initialization params
    const workspaceUri = workspaceFolders?.[0]?.uri ?? rootUri;
    if (workspaceUri) {
      const workspaceRoot = fileURLToPath(workspaceUri);
      configStore.setWorkspaceRoot(workspaceRoot);
      connection.console.info(`Workspace root: ${workspaceRoot}`);
    }

    configStore.setDiagnosticRelatedInformationCapability(!!(capabilities.textDocument
      && capabilities.textDocument.publishDiagnostics
      && capabilities.textDocument.publishDiagnostics.relatedInformation));

    configStore.setEnableWarningDiagnostics(!!(initializationOptions?.enableWarningDiagnostics));
    configStore.setEnableFormatting(!!(initializationOptions?.enableFormatting));

    connection.console.info(`Initialized with warningDiagnostics=${configStore.isWarningDiagnosticsEnabled()}, formatting=${configStore.isFormattingEnabled()}`);

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
        documentFormattingProvider: configStore.isFormattingEnabled(),
        codeActionProvider: {
          codeActionKinds: [CodeActionKind.QuickFix],
          resolveProvider: true,
        },
        workspace: {
          workspaceFolders: {
            supported: configStore.hasWorkspaceFolders(),
          },
        },
      },
    };
    return result;
  });

  connection.onDidChangeConfiguration(({ settings }) => {
    configStore.setEnableWarningDiagnostics(!!(settings?.enableWarningDiagnostics));
  });
}
