import type { Position } from 'vscode-languageserver-textdocument';
import type {
  CancellationToken,
  CodeAction,
  CodeActionParams,
  CompletionItem,
  Definition,
  DefinitionParams,
  Diagnostic,
  DocumentDiagnosticReport,
  DocumentSymbol,
  DocumentSymbolParams,
  Hover,
  HoverParams,
  InitializeParams,
  InitializeResult,
  Location,
  Range,
  ReferenceParams,
  TextDocumentPositionParams,
} from 'vscode-languageserver/node';
import type { Field, Definition as KiwiDefinition, Schema } from './schema';
import type { FilePosition, KiwiParseError } from './util';
import * as fs from 'node:fs';
import * as path from 'node:path';
import { camelCase, constantCase, pascalCase, sentenceCase } from 'change-case';
import { TextDocument } from 'vscode-languageserver-textdocument';
import {
  CodeActionKind,
  CompletionItemKind,
  createConnection,
  DiagnosticRelatedInformation,
  DiagnosticSeverity,
  DiagnosticTag,
  DocumentDiagnosticReportKind,
  ProposedFeatures,
  SymbolKind,
  TextDocuments,
  TextDocumentSyncKind,
  TextEdit,
} from 'vscode-languageserver/node';
import { nativeTypes, parseSchema } from './parser';
import {
  convertPosition,
  isCamelCase,
  isInsideRange,
  isPascalCase,
  isPositionInFile,
  isScreamingSnakeCase,
  parseIncludes,
  readKiwiFile,
  uriToFilePath,
} from './util';

const connection = createConnection(ProposedFeatures.all);

const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

let hasWorkspaceFolderCapability = false;
let hasDiagnosticRelatedInformationCapability = false;

connection.onInitialize((params: InitializeParams) => {
  const capabilities = params.capabilities;

  hasWorkspaceFolderCapability = !!(
    capabilities.workspace && !!capabilities.workspace.workspaceFolders
  );
  hasDiagnosticRelatedInformationCapability = !!(
    capabilities.textDocument
    && capabilities.textDocument.publishDiagnostics
    && capabilities.textDocument.publishDiagnostics.relatedInformation
  );

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
  if (hasWorkspaceFolderCapability) {
    result.capabilities.workspace = {
      workspaceFolders: {
        supported: true,
      },
    };
  }
  return result;
});

connection.languages.diagnostics.on(async (params) => {
  const document = documents.get(params.textDocument.uri);
  return {
    kind: DocumentDiagnosticReportKind.Full,
    items: document ? await validateTextDocument(document) : [],
  } satisfies DocumentDiagnosticReport;
});

documents.onDidChangeContent(change => validateTextDocument(change.document));

const files: Record<string, Schema> = {};

async function validateTextDocument(textDocument: TextDocument): Promise<Diagnostic[]> {
  const filePath = uriToFilePath(textDocument.uri);
  const { content: combinedText, filePositions } = readKiwiFile(filePath);

  let schema: Schema | undefined;
  let errors: KiwiParseError[] = [];

  try {
    const [parsed, validateErrors] = parseSchema(combinedText);
    files[textDocument.uri] = parsed;
    schema = parsed;
    errors = validateErrors;
  }
  catch (e: any) {
    errors.push(e);
  }

  // 过滤并调整诊断信息
  const diagnostics: Diagnostic[] = errors
    .filter((e) => {
      // 只保留当前文件的错误
      return isPositionInFile(e.range.start.line, filePath, filePositions);
    })
    .map((e) => {
      // 调整错误范围到原始文件中的位置
      const adjustedRange = {
        start: {
          line: convertPosition(e.range.start.line, filePath, filePositions),
          character: e.range.start.character,
        },
        end: {
          line: convertPosition(e.range.end.line, filePath, filePositions),
          character: e.range.end.character,
        },
      };

      return {
        message: e.message,
        range: adjustedRange,
        relatedInformation: e.relatedInformation && hasDiagnosticRelatedInformationCapability
          ? [DiagnosticRelatedInformation.create(
              { uri: textDocument.uri, range: adjustedRange },
              e.relatedInformation.message,
            )]
          : undefined,
        severity: DiagnosticSeverity.Error,
        source: 'kiwi',
        data: e.errorKind,
      };
    });

  // 添加样式诊断
  if (schema) {
    for (const def of schema.definitions) {
      // 跳过非当前文件的定义
      if (!isPositionInFile(def.nameSpan.start.line, filePath, filePositions)) {
        continue;
      }

      // 调整定义的位置
      const adjustedNameSpan = {
        start: {
          line: convertPosition(def.nameSpan.start.line, filePath, filePositions),
          character: def.nameSpan.start.character,
        },
        end: {
          line: convertPosition(def.nameSpan.end.line, filePath, filePositions),
          character: def.nameSpan.end.character,
        },
      };

      if (!isPascalCase(def.name)) {
        diagnostics.push({
          message: `${sentenceCase(def.kind)} names should be PascalCase`,
          range: adjustedNameSpan,
          severity: DiagnosticSeverity.Warning,
          source: 'kiwi',
          data: { kind: 'change case', newText: pascalCase(def.name) },
        });
      }

      if (def.kind === 'ENUM') {
        for (const field of def.fields) {
          if (isScreamingSnakeCase(field.name)) {
            continue;
          }

          diagnostics.push({
            message: 'Enum variants should be SCREAMING_SNAKE_CASE',
            range: field.nameSpan,
            severity: DiagnosticSeverity.Warning,
            source: 'kiwi',
            data: { kind: 'change case', newText: constantCase(field.name) },
          });
        }
      }
      else {
        for (const field of def.fields) {
          // 调整字段位置
          const adjustedFieldSpan = {
            start: {
              line: convertPosition(field.nameSpan.start.line, filePath, filePositions),
              character: field.nameSpan.start.character,
            },
            end: {
              line: convertPosition(field.nameSpan.end.line, filePath, filePositions),
              character: field.nameSpan.end.character,
            },
          };

          if (field.isDeprecated) {
            diagnostics.push({
              message: 'Field deprecated',
              range: adjustedFieldSpan,
              tags: [DiagnosticTag.Deprecated],
              severity: DiagnosticSeverity.Hint,
              source: 'kiwi',
            });
          }

          if (!isCamelCase(field.name)) {
            diagnostics.push({
              message: 'Field names should be camelCase',
              range: adjustedFieldSpan,
              severity: DiagnosticSeverity.Warning,
              source: 'kiwi',
              data: { kind: 'change case', newText: camelCase(field.name) },
            });
          }
        }
      }
    }

    if (schema.package && !isPascalCase(schema.package.text)) {
      diagnostics.push({
        message: 'Package names should be PascalCase',
        range: schema.package.span,
        severity: DiagnosticSeverity.Warning,
        source: 'kiwi',
        data: { kind: 'change case', newText: pascalCase(schema.package.text) },
      });
    }
  }

  // 处理重复定义的相关信息
  for (const e of errors) {
    if (!e.relatedInformation || !hasDiagnosticRelatedInformationCapability) {
      continue;
    }

    const adjustedRange = {
      start: {
        line: convertPosition(e.range.start.line, filePath, filePositions),
        character: e.range.start.character,
      },
      end: {
        line: convertPosition(e.range.end.line, filePath, filePositions),
        character: e.range.end.character,
      },
    };

    diagnostics.push({
      message: 'First definition here',
      range: e.relatedInformation.span,
      relatedInformation: [DiagnosticRelatedInformation.create(
        { uri: textDocument.uri, range: adjustedRange },
        'Duplicated here',
      )],
      severity: DiagnosticSeverity.Hint,
      source: 'kiwi',
      data: e.errorKind,
    });
  }

  return diagnostics;
}

const PRIMITIVE_TYPE_DOCS: Record<string, string> = {
  bool: 'A value that stores either true or false',
  byte: 'An unsigned 8-bit integer value',
  int: 'A signed 32-bit integer',
  uint: 'An unsigned 32-bit integer',
  int64: 'A signed 64-bit integer',
  float: 'A 32-bit floating-point number',
  uint64: 'An unsigned 64-bit integer',
  string: 'A UTF-8 null-terminated string',
};

const KEYWORD_DOCS: Record<string, string> = {
  enum: '',
  struct:
    'An object whose fields are required. More space efficient than a message, but should be used sparingly due to back-compat.',
  message:
    'An object whose fields are optional. The default structure in a kiwi document.',
};

function getSchema(uri: string): Schema | undefined {
  try {
    const document = documents.get(uri);
    const [parsed, _errors] = parseSchema(document!.getText());
    files[uri] = parsed;
  }
  catch {
    //
  }

  return files[uri];
}

connection.onReferences(
  (params: ReferenceParams): Location[] => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
      return [];
    }

    const filePath = uriToFilePath(document.uri);
    connection.console.log(`Finding references in ${filePath} at position ${params.position.line}:${params.position.character}`);

    // 获取当前文件及其所有依赖的 Schema
    const allSchemas = new Map<string, Schema>();
    const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

    // 首先加载当前文件
    const currentFileContent = readKiwiFile(filePath);
    fileContents.set(filePath, currentFileContent);
    const schema = getSchema(params.textDocument.uri);
    if (!schema) {
      return [];
    }
    allSchemas.set(filePath, schema);

    // 加载所有依赖文件
    const includedSchemas = loadIncludedSchemas(filePath);
    for (const [path, schema] of includedSchemas) {
      allSchemas.set(path, schema);
      const content = readKiwiFile(path);
      fileContents.set(path, content);
    }

    connection.console.log(`Loaded ${allSchemas.size} schemas for reference search`);

    // 找到点击位置的定义
    let targetName: string | undefined;
    let targetLoc: Location | undefined;

    // 检查是否点击在定义名称上
    for (const def of schema.definitions) {
      if (isInsideRange(params.position, def.nameSpan)) {
        targetName = def.name;
        targetLoc = {
          uri: params.textDocument.uri,
          range: def.nameSpan,
        };
        break;
      }

      // 检查是否点击在字段类型上
      if (def.kind !== 'ENUM' && isInsideRange(params.position, def.fieldsSpan)) {
        for (const field of def.fields) {
          if (field.typeSpan && isInsideRange(params.position, field.typeSpan)) {
            targetName = field.type;
            targetLoc = {
              uri: params.textDocument.uri,
              range: field.typeSpan,
            };
            break;
          }
        }
        if (targetName)
          break;
      }
    }

    if (!targetName) {
      connection.console.log('No definition found at cursor position');
      return [];
    }

    connection.console.log(`Found definition ${targetName}, searching for references`);

    const references: Location[] = [];

    // 在所有文件中搜索引用
    for (const [path, schema] of allSchemas) {
      const fileContent = fileContents.get(path);
      if (!fileContent)
        continue;

      // 在定义中搜索引用
      for (const def of schema.definitions) {
        // 检查定义名称
        if (def.name === targetName) {
          references.push({
            uri: pathToFileURL(path),
            range: def.nameSpan,
          });
        }

        // 检查字段类型
        if (def.kind !== 'ENUM') {
          for (const field of def.fields) {
            if (field.type === targetName && field.typeSpan) {
              // 调整位置到原始文件
              const adjustedRange = {
                start: {
                  line: convertPosition(field.typeSpan.start.line, path, fileContent.filePositions),
                  character: field.typeSpan.start.character,
                },
                end: {
                  line: convertPosition(field.typeSpan.end.line, path, fileContent.filePositions),
                  character: field.typeSpan.end.character,
                },
              };

              references.push({
                uri: pathToFileURL(path),
                range: adjustedRange,
              });
            }
          }
        }
      }
    }

    // 如果需要包含声明，并且找到了目标位置
    if (params.context.includeDeclaration && targetLoc) {
      references.push(targetLoc);
    }

    connection.console.log(`Found ${references.length} references`);
    return references;
  },
);

/**
 * 将文件路径转换为 URI
 */
function pathToFileURL(filePath: string): string {
  return `file://${filePath}`;
}

function findContainingDefinition(
  position: Position,
  schema: Schema,
): KiwiDefinition | undefined {
  return schema.definitions.find(def => isInsideRange(position, def.defSpan));
}

connection.onHover((params: HoverParams, _token: CancellationToken): Hover => {
  const schema = getSchema(params.textDocument.uri);

  if (!schema) {
    return { contents: [] };
  }

  const formatForDef = (def: KiwiDefinition): string[] => {
    const notes = [`(${def.kind.toLowerCase()}) ${def.name}`];

    if (def.fields.length <= 3) {
      return notes;
    }

    if (def.kind === 'ENUM') {
      notes.push(`${def.fields.length} variants`);
    }
    else {
      notes.push(`${def.fields.length} fields | next id ${def.fields.length + 1}`);
    }

    return notes;
  };

  const def = findContainingDefinition(params.position, schema);

  if (!def) {
    return { contents: [] };
  }

  if (isInsideRange(params.position, def.keywordSpan)) {
    return { contents: KEYWORD_DOCS[def.kind.toLowerCase()] };
  }

  if (isInsideRange(params.position, def.nameSpan)) {
    return { contents: formatForDef(def), range: def.nameSpan };
  }

  let target: Field | undefined;

  if (isInsideRange(params.position, def.fieldsSpan)) {
    for (const field of def.fields) {
      if (isInsideRange(params.position, field.typeSpan)) {
        if (PRIMITIVE_TYPE_DOCS[field.type!]) {
          return {
            contents: `(builtin) ${PRIMITIVE_TYPE_DOCS[field.type!]}`,
            range: field.typeSpan,
          };
        }

        target = field;

        break;
      }

      if (isInsideRange(params.position, field.deprecatedSpan)) {
        return { contents: ['Deprecated fields are ignored during codegen'] };
      }

      if (isInsideRange(params.position, field.nameSpan)) {
        break;
      }
    }
  }

  if (target) {
    const def = schema.definitions.find(def => def.name === target?.type);

    if (def) {
      return {
        contents: `(${def.kind.toLowerCase()}) ${def.name}`,
        range: target.typeSpan,
      };
    }
  }

  return { contents: [] };
});

connection.onDefinition((params: DefinitionParams): Definition | null => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }

  const filePath = uriToFilePath(document.uri);
  connection.console.log(`Finding definition in ${filePath} at position ${params.position.line}:${params.position.character}`);

  // 首先检查是否点击的是 include 路径
  const text = document.getText();
  const includes = parseIncludes(text);
  for (const include of includes) {
    if (isPositionInRange(params.position, include.pathRange)) {
      const currentDir = path.dirname(filePath);
      const targetPath = path.resolve(currentDir, include.path);
      return {
        uri: pathToFileURL(targetPath),
        range: { start: { line: 0, character: 0 }, end: { line: 0, character: 0 } },
      };
    }
  }

  // 获取当前文件及其所有依赖的 Schema
  const allSchemas = new Map<string, Schema>();
  const fileContents = new Map<string, { content: string; filePositions: FilePosition[] }>();

  // 加载当前文件
  const currentFileContent = readKiwiFile(filePath);
  fileContents.set(filePath, currentFileContent);
  const schema = getSchema(params.textDocument.uri);
  if (!schema) {
    return null;
  }
  allSchemas.set(filePath, schema);

  // 加载所有依赖文件
  const includedSchemas = loadIncludedSchemas(filePath);
  for (const [path, schema] of includedSchemas) {
    allSchemas.set(path, schema);
    const content = readKiwiFile(path);
    fileContents.set(path, content);
  }

  connection.console.log(`Loaded ${allSchemas.size} schemas for definition lookup`);

  // 在当前文件中查找点击的类型
  let targetType: string | undefined;

  // 检查是否点击在字段类型上
  for (const def of schema.definitions) {
    if (def.kind !== 'ENUM' && isInsideRange(params.position, def.fieldsSpan)) {
      for (const field of def.fields) {
        if (field.typeSpan && isInsideRange(params.position, field.typeSpan)) {
          targetType = field.type;
          break;
        }
      }
      if (targetType)
        break;
    }
  }

  if (!targetType) {
    connection.console.log('No type found at cursor position');
    return null;
  }

  connection.console.log(`Looking for definition of type ${targetType}`);

  // 在所有文件中查找类型定义
  for (const [path, schema] of allSchemas) {
    const fileContent = fileContents.get(path);
    if (!fileContent)
      continue;

    for (const def of schema.definitions) {
      if (def.name === targetType) {
        // 调整位置到原始文件
        const adjustedRange = {
          start: {
            line: convertPosition(def.nameSpan.start.line, path, fileContent.filePositions),
            character: def.nameSpan.start.character,
          },
          end: {
            line: convertPosition(def.nameSpan.end.line, path, fileContent.filePositions),
            character: def.nameSpan.end.character,
          },
        };

        connection.console.log(`Found definition in ${path}`);
        return {
          uri: pathToFileURL(path),
          range: adjustedRange,
        };
      }
    }
  }

  connection.console.log('Definition not found');
  return null;
});

/**
 * 递归加载文件的所有依赖
 */
function loadIncludedSchemas(filePath: string): Map<string, Schema> {
  const schemas = new Map<string, Schema>();
  const visited = new Set<string>();

  function load(currentPath: string) {
    if (visited.has(currentPath))
      return;
    visited.add(currentPath);

    try {
      const content = fs.readFileSync(currentPath, 'utf8');
      const [schema, _] = parseSchema(content);
      schemas.set(currentPath, schema);

      // 处理该文件的 includes
      const includes = parseIncludes(content);
      for (const include of includes) {
        const includePath = path.resolve(path.dirname(currentPath), include.path);
        load(includePath);
      }
    }
    catch (error) {
      connection.console.error(`Error loading schema from ${currentPath}: ${error}`);
    }
  }

  load(filePath);
  return schemas;
}

// Helper functions
function isPositionInRange(position: Position, range: Range): boolean {
  if (position.line !== range.start.line)
    return false;
  return position.character >= range.start.character
    && position.character <= range.end.character;
}

connection.onDocumentSymbol((params: DocumentSymbolParams): DocumentSymbol[] => {
  const schema = getSchema(params.textDocument.uri);

  if (!schema) {
    return [];
  }

  const symbols: DocumentSymbol[] = [];

  if (schema.package) {
    symbols.push({
      name: schema.package.text,
      kind: SymbolKind.Package,
      range: schema.package.span,
      selectionRange: schema.package.span,
    });
  }

  for (const def of schema.definitions) {
    symbols.push({
      name: def.name,
      kind: def.kind === 'ENUM' ? SymbolKind.Enum : SymbolKind.Class,
      range: def.defSpan,
      selectionRange: def.nameSpan,
    });

    for (const field of def.fields) {
      symbols.push({
        name: field.name,
        kind: def.kind === 'ENUM' ? SymbolKind.EnumMember : SymbolKind.Field,
        range: field.span,
        selectionRange: field.nameSpan,
      });
    }
  }

  return symbols;
});

function getNextId(def: KiwiDefinition): number | undefined {
  if (def.kind !== 'MESSAGE') {
    return;
  }

  const usedIds = new Set(def.fields.map(f => f.value));

  for (let i = 1; i < def.fields.length; i++) {
    if (!usedIds.has(i)) {
      return i;
    }
  }

  return def.fields.length;
}

connection.onCodeAction((params: CodeActionParams): CodeAction[] => {
  const diagnostics = params.context.diagnostics.filter(d => !!d.data);

  if (diagnostics.length === 0) {
    return [];
  }

  const schema = getSchema(params.textDocument.uri);

  if (!schema) {
    return [];
  }

  const def = findContainingDefinition(params.range.start, schema);

  function getNextIdQuickActions() {
    const nextIdDiagnostics = diagnostics.filter(d => d.data === 'invalid id');

    if (!def || def.kind !== 'MESSAGE') {
      return [];
    }

    return nextIdDiagnostics.map(diagnostic => ({
      title: 'Use next available id',
      kind: CodeActionKind.QuickFix,
      diagnostics: [diagnostic],
      edit: {
        changes: {
          [params.textDocument.uri]: [
            TextEdit.replace(diagnostic.range, `${getNextId(def)}`),
          ],
        },
      },
    }));
  }

  function getChangeCaseQuickActions() {
    const changeCaseDiagnostics = diagnostics.filter(
      d => d.data?.kind === 'change case',
    );

    if (!def) {
      return [];
    }

    return changeCaseDiagnostics.map(diagnostic => ({
      title: 'Change case',
      kind: CodeActionKind.QuickFix,
      diagnostics: [diagnostic],
      edit: {
        changes: {
          [params.textDocument.uri]: [
            TextEdit.replace(diagnostic.range, diagnostic.data?.newText),
          ],
        },
      },
    }));
  }

  return [...getNextIdQuickActions(), ...getChangeCaseQuickActions()];
});

connection.onCompletion(
  (textDocumentPosition: TextDocumentPositionParams): CompletionItem[] => {
    const document = documents.get(textDocumentPosition.textDocument.uri);
    if (!document) {
      return [];
    }

    const filePath = uriToFilePath(document.uri);
    connection.console.log(`Computing completions for ${filePath} at line ${textDocumentPosition.position.line}`);

    // 获取当前文件及其所有依赖的 Schema
    const allSchemas = new Map<string, Schema>();

    // 首先加载当前文件
    const schema = getSchema(textDocumentPosition.textDocument.uri);
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
      ...nativeTypes.map(ty => ({
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
          detail: `(${d.kind.toLowerCase()} from ${
            schema === allSchemas.get(filePath) ? 'current file' : 'imported file'
          })`,
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

documents.listen(connection);
connection.listen();
