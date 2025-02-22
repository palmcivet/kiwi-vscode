import type { Definition } from '@server/parser';
import type { FileStore } from '@server/store';
import type { CodeAction, CodeActionParams } from 'vscode-languageserver/node';
import type { ServerConnection } from './type';
import { isInsideRange } from '@server/helper';
import { CodeActionKind, TextEdit } from 'vscode-languageserver/node';

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

export function setupOnCodeAction(connection: ServerConnection, fileStore: FileStore): void {
  connection.onCodeAction((params: CodeActionParams): CodeAction[] => {
    const diagnostics = params.context.diagnostics.filter(d => !!d.data);

    if (diagnostics.length === 0) {
      return [];
    }

    const schema = fileStore.loadTextSchema(params.textDocument.uri);
    if (!schema) {
      return [];
    }

    const def = schema.definitions.find(def => isInsideRange(params.range.start, def.defSpan));

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
