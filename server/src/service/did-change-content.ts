import type { KiwiParseError, Schema } from '@server/parser';
import type { FileStore } from '@server/store';
import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { Diagnostic, DocumentDiagnosticReport } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import {
  isCamelCase,
  isPascalCase,
  isScreamingSnakeCase,
} from '@server/helper';
import {
  convertPosition,
  fileUriToPath,
  isPositionInFile,
  parseSchema,
  readKiwiDocument,
} from '@server/parser';
import { configStore } from '@server/store';
import { camelCase, constantCase, pascalCase, sentenceCase } from 'change-case';
import {
  DiagnosticRelatedInformation,
  DiagnosticSeverity,
  DiagnosticTag,
  DocumentDiagnosticReportKind,
} from 'vscode-languageserver/node';

/**
 * Validates a text document and generates diagnostics.
 * This includes syntax errors, style warnings, and other language-specific issues.
 *
 * @param textDocument - The document to validate
 * @returns Array of diagnostic messages for the document
 */
function validateTextDocument(textDocument: TextDocument): Diagnostic[] {
  const filePath = fileUriToPath(textDocument.uri);
  const { content: combinedText, filePositions } = readKiwiDocument(textDocument);

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

  // Filter and adjust diagnostic information
  const diagnostics: Diagnostic[] = errors
    .filter((e) => {
      // Only keep errors from the current file
      return isPositionInFile(e.range.start.line, filePath, filePositions);
    })
    .map((e) => {
      // Adjust error ranges to positions in the original file
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
        relatedInformation: e.relatedInformation && configStore.hasDiagnosticRelatedInformation()
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

  // Add style diagnostics only if warning diagnostics are enabled
  if (schema && configStore.isWarningDiagnosticsEnabled()) {
    for (const def of schema.definitions) {
      // Skip definitions not in the current file
      if (!isPositionInFile(def.nameSpan.start.line, filePath, filePositions)) {
        continue;
      }

      // Adjust definition position
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

      // Check for PascalCase in definition names
      if (!isPascalCase(def.name)) {
        diagnostics.push({
          message: `${sentenceCase(def.kind)} names should be PascalCase`,
          range: adjustedNameSpan,
          severity: DiagnosticSeverity.Warning,
          source: 'kiwi',
          data: { kind: 'change case', newText: pascalCase(def.name) },
        });
      }

      // Handle enum fields
      if (def.kind === 'ENUM') {
        for (const field of def.fields) {
          if (isScreamingSnakeCase(field.name)) {
            continue;
          }

          diagnostics.push({
            message: 'Enum variants should be SCREAMING_SNAKE_CASE',
            range: {
              start: {
                line: convertPosition(field.nameSpan.start.line, filePath, filePositions),
                character: field.nameSpan.start.character,
              },
              end: {
                line: convertPosition(field.nameSpan.end.line, filePath, filePositions),
                character: field.nameSpan.end.character,
              },
            },
            severity: DiagnosticSeverity.Warning,
            source: 'kiwi',
            data: { kind: 'change case', newText: constantCase(field.name) },
          });
        }
      }
      // Handle struct/message fields
      else {
        for (const field of def.fields) {
          // Adjust field position
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

          // Check for deprecated fields
          if (field.isDeprecated) {
            diagnostics.push({
              message: 'Field deprecated',
              range: adjustedFieldSpan,
              tags: [DiagnosticTag.Deprecated],
              severity: DiagnosticSeverity.Hint,
              source: 'kiwi',
            });
          }

          // Check for camelCase in field names
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

    // Check package name case
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

  // Handle duplicate definition information
  for (const e of errors) {
    if (!e.relatedInformation || !configStore.hasDiagnosticRelatedInformation()) {
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

/**
 * Sets up the content change handler for the language server.
 * This includes:
 * 1. Diagnostic report generation when requested
 * 2. Real-time validation as content changes
 *
 * @param connection - The server connection instanc
 * @param fileStore - Store managing schema documents and their dependencies
 */
export function setupOnDidChangeContent(connection: ServerConnection, fileStore: FileStore): void {
  connection.languages.diagnostics.on((params) => {
    const document = fileStore.getTextDocument(params.textDocument.uri);
    return {
      kind: DocumentDiagnosticReportKind.Full,
      items: document ? validateTextDocument(document) : [],
    } satisfies DocumentDiagnosticReport;
  });
}
