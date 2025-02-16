import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { CodeAction, CodeActionParams, TextDocuments } from 'vscode-languageserver/node';
import type { Definition } from '../parser';
import type { ServerConnection } from './util';
import { CodeActionKind, TextEdit } from 'vscode-languageserver/node';
import { findContainingDefinition, getSchema } from './util';

function getNextId(def: Definition): number | undefined {
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

export function setupOnCodeAction(connection: ServerConnection, documents: TextDocuments<TextDocument>): void {
  connection.onCodeAction((params: CodeActionParams): CodeAction[] => {
    const diagnostics = params.context.diagnostics.filter(d => !!d.data);

    if (diagnostics.length === 0) {
      return [];
    }

    const schema = getSchema(params.textDocument.uri, documents);
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
}
