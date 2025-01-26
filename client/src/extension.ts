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

  client.info('扩展激活');
  client.info(`服务器模块路径: ${serverModule}`);

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

  client.start();
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) {
    return undefined;
  }
  return client.stop();
}
