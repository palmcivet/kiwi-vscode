import * as path from 'path';
import { workspace, ExtensionContext } from 'vscode';

import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from 'vscode-languageclient/node';

let client: LanguageClient;

export function activate(context: ExtensionContext) {
  const serverModule = context.asAbsolutePath(path.join('server', 'out', 'server.js'));

  const serverOptions: ServerOptions = {
    run: { module: serverModule, transport: TransportKind.ipc },
    debug: {
      module: serverModule,
      transport: TransportKind.ipc,
    },
  };

  // 获取配置
  const config = workspace.getConfiguration('kiwi-vscode');
  const includeFiles = config.get<string[]>('includeFiles') || [];

  // 创建客户端配置
  const clientOptions: LanguageClientOptions = {
    documentSelector: [{ scheme: 'file', language: 'kiwi' }],
    synchronize: {
      fileEvents: workspace.createFileSystemWatcher('**/*.kiwi'),
    },
    initializationOptions: {
      includeFiles,
    },
  };

  client = new LanguageClient(
    'kiwivscode',
    'Kiwi VSCode',
    serverOptions,
    clientOptions
  );

  client.start();
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) {
    return undefined;
  }
  return client.stop();
}
