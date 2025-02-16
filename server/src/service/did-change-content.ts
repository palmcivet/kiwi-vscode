import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { Diagnostic, DocumentDiagnosticReport, TextDocuments } from 'vscode-languageserver/node';
import type { KiwiParseError, Schema } from '../parser';
import type { ServerConnection } from './type';
import { camelCase, constantCase, pascalCase, sentenceCase } from 'change-case';
import {
  DiagnosticRelatedInformation,
  DiagnosticSeverity,
  DiagnosticTag,
  DocumentDiagnosticReportKind,
} from 'vscode-languageserver/node';
import {
  isCamelCase,
  isPascalCase,
  isScreamingSnakeCase,
} from '../helper';
import {
  convertPosition,
  fileUriToPath,
  isPositionInFile,
  parseSchema,
  readKiwiFile,
} from '../parser';
import { serverStore } from './store';

function validateTextDocument(textDocument: TextDocument): Diagnostic[] {
  const filePath = fileUriToPath(textDocument.uri);
  const { content: combinedText, filePositions } = readKiwiFile(filePath);

  let schema: Schema | undefined;
  let errors: KiwiParseError[] = [];

  try {
    // TODO cache schema
    const [parsed, validateErrors] = parseSchema(combinedText);
    schema = parsed;
    errors = validateErrors;
  }
  catch (error: any) {
    errors.push(error);
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
        relatedInformation: e.relatedInformation && serverStore.hasDiagnosticRelatedInformation()
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
    if (!e.relatedInformation || !serverStore.hasDiagnosticRelatedInformation()) {
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

export function setupOnDidChangeContent(connection: ServerConnection, documents: TextDocuments<TextDocument>): void {
  connection.languages.diagnostics.on((params) => {
    const document = documents.get(params.textDocument.uri);
    return {
      kind: DocumentDiagnosticReportKind.Full,
      items: document ? validateTextDocument(document) : [],
    } satisfies DocumentDiagnosticReport;
  });

  documents.onDidChangeContent(({ document }) => {
    const diagnostics = validateTextDocument(document);
    connection.sendDiagnostics({ uri: document.uri, diagnostics });
  });
}
