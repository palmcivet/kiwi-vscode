import * as path from 'path';
import {
  workspace,
  languages,
  type ExtensionContext,
  type TextDocument,
  type FormattingOptions,
  type TextEdit,
} from 'vscode';

import {
  LanguageClient,
  TransportKind,
  type LanguageClientOptions,
  type ServerOptions,
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
  const formatEnabled = config.get<boolean>('formatEnabled') || false;

  // 创建客户端配置
  const clientOptions: LanguageClientOptions = {
    documentSelector: [{ scheme: 'file', language: 'kiwi' }],
    synchronize: {
      fileEvents: workspace.createFileSystemWatcher('**/*.kiwi'),
    },
    initializationOptions: {
      includeFiles,
      formatEnabled,
    },
  };

  client = new LanguageClient('kiwivscode', 'Kiwi VSCode', serverOptions, clientOptions);

  client.info('Starting Kiwi LSP');
  client.info(`Server module location: ${serverModule}`);

  // 注册格式化 Provider
  context.subscriptions.push(
    languages.registerDocumentFormattingEditProvider('kiwi', {
      async provideDocumentFormattingEdits(
        document: TextDocument,
        options: FormattingOptions
      ): Promise<TextEdit[]> {
        // 委托给语言服务器处理格式化
        const params = {
          textDocument: { uri: document.uri.toString() },
          options,
        };
        try {
          return await client.sendRequest('textDocument/formatting', params);
        } catch (error) {
          return [];
        }
      },
    })
  );

  // 添加配置变更监听
  context.subscriptions.push(
    workspace.onDidChangeConfiguration((e) => {
      if (e.affectsConfiguration('kiwi-vscode')) {
        // 通知服务端配置已更新
        client.sendNotification('workspace/didChangeConfiguration', {
          settings: workspace.getConfiguration('kiwi-vscode'),
        });
      }
    })
  );

  client.start();
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) {
    return undefined;
  }
  return client.stop();
}
