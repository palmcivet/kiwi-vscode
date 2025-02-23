import type { ExtensionContext } from 'vscode';
import type { LanguageClientOptions, ServerOptions } from 'vscode-languageclient/node';
import { join } from 'node:path';
import { PluginKey } from '@client/constant';
import { workspace } from 'vscode';
import { LanguageClient, TransportKind } from 'vscode-languageclient/node';

let client: LanguageClient;

export function activate(context: ExtensionContext) {
  const serverModule = context.asAbsolutePath(join('server', 'out', 'server.js'));

  const serverOptions: ServerOptions = {
    run: { module: serverModule, transport: TransportKind.ipc },
    debug: {
      module: serverModule,
      transport: TransportKind.ipc,
    },
  };

  const clientOptions: LanguageClientOptions = {
    documentSelector: [{ scheme: 'file', language: 'kiwi' }],
    synchronize: {
      fileEvents: workspace.createFileSystemWatcher('**/.clientrc'),
    },
    initializationOptions: {
      enableWarningDiagnostics: workspace.getConfiguration(PluginKey).get('enableWarningDiagnostics'),
    },
  };

  client = new LanguageClient(
    'KiwiLanguageServer',
    'Kiwi Language Server',
    serverOptions,
    clientOptions,
  );

  context.subscriptions.push(
    workspace.onDidChangeConfiguration((event) => {
      if (!event.affectsConfiguration(PluginKey)) {
        return;
      }

      client.sendNotification('workspace/didChangeConfiguration', {
        settings: {
          enableWarningDiagnostics: workspace.getConfiguration(PluginKey).get('enableWarningDiagnostics'),
        },
      });
    }),
  );

  client.start();
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) {
    return undefined;
  }
  return client.stop();
}
