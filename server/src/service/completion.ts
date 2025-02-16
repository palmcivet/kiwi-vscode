import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { CompletionItem, TextDocumentPositionParams, TextDocuments } from 'vscode-languageserver/node';
import type { Schema } from '../parser';
import type { ServerConnection } from './util';
import { CompletionItemKind } from 'vscode-languageserver/node';
import { fileUriToPath, NativeTypes } from '../parser';
import { getSchema, loadIncludedSchemas } from './util';

export function setupOnCompletion(connection: ServerConnection, documents: TextDocuments<TextDocument>): void {
  connection.onCompletion(
    (textDocumentPosition: TextDocumentPositionParams): CompletionItem[] => {
      const document = documents.get(textDocumentPosition.textDocument.uri);
      if (!document) {
        return [];
      }

      const filePath = fileUriToPath(document.uri);
      connection.console.log(`Computing completions for ${filePath} at line ${textDocumentPosition.position.line}`);

      // 获取当前文件及其所有依赖的 Schema
      const allSchemas = new Map<string, Schema>();

      // 首先加载当前文件
      const schema = getSchema(textDocumentPosition.textDocument.uri, documents);
      if (!schema) {
        connection.console.log(`No schema found for ${filePath}`);
        return [];
      }
      allSchemas.set(filePath, schema);

      // 加载所有依赖文件
      const includedSchemas = loadIncludedSchemas(filePath);
      for (const [path, schema] of includedSchemas) {
        allSchemas.set(path, schema);
      }

      // 收集所有可用的类型
      const typeCompletions: CompletionItem[] = [
        ...NativeTypes.map(ty => ({
          label: ty,
          kind: CompletionItemKind.Field,
          detail: '(builtin type)',
        })),
        ...Array.from(allSchemas.values()).flatMap(schema =>
          schema.definitions.map(d => ({
            label: d.name,
            kind: d.kind === 'ENUM'
              ? CompletionItemKind.Enum
              : d.kind === 'STRUCT'
                ? CompletionItemKind.Interface
                : CompletionItemKind.Class,
            detail: `(${d.kind.toLowerCase()} from ${schema === allSchemas.get(filePath) ? 'current file' : 'imported file'})`,
          })),
        ),
      ];

      const toplevelCompletions = ['message ', 'struct ', 'enum '].map(kw => ({
        label: kw,
        kind: CompletionItemKind.Keyword,
        detail: '(declaration)',
      }));

      // 获取当前行的文本和光标位置
      const lines = document.getText().split('\n');
      const currentLine = lines[textDocumentPosition.position.line];
      const currentCharacter = textDocumentPosition.position.character;

      connection.console.log(`Current line: "${currentLine}"`);
      connection.console.log(`Current character: ${currentCharacter}`);

      // 分析当前行的上下文
      const linePrefix = currentLine.slice(0, currentCharacter).trim();

      // 如果当前行是空的或只有空白字符，提供顶层补全
      if (!linePrefix) {
        if (!schema.package && textDocumentPosition.position.line === 0) {
          toplevelCompletions.push({
            label: 'package ',
            kind: CompletionItemKind.Keyword,
            detail: '(declaration)',
          });
        }
        return toplevelCompletions;
      }

      // 检查是否在消息定义内部
      const messageMatch = /^\s*message\s+\w+\s*\{/.test(currentLine);
      if (messageMatch) {
        return typeCompletions;
      }

      // 检查是否在字段定义中
      const fieldMatch = /^\s*(\w+\s+)?(\w*)$/.exec(linePrefix);
      if (fieldMatch) {
        const [, typePart, _fieldPart] = fieldMatch;

        // 如果已经输入了类型，提供字段名建议
        if (typePart) {
          return [{
            label: 'deprecated',
            kind: CompletionItemKind.Keyword,
            detail: '(field modifier)',
          }];
        }

        // 否则提供类型建议
        return typeCompletions;
      }

      // 默认提供顶层补全
      return toplevelCompletions;
    },
  );
}
