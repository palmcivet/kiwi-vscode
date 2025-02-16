import type { CancellationToken, Hover, HoverParams } from 'vscode-languageserver/node';
import type { Definition, Field } from '../parser';
import type { FileStore } from '../store/file-store';
import type { ServerConnection } from './type';
import {
  isInsideFieldsDefinition,
  isInsideLineRange,
  isInsideRange,
  isInsideTypeReference,
} from '../helper';

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

export function setupOnHover(connection: ServerConnection, fileStore: FileStore): void {
  connection.onHover((params: HoverParams, _token: CancellationToken): Hover => {
    const schema = fileStore.loadTextSchema(params.textDocument.uri);

    if (!schema) {
      return { contents: [] };
    }

    const formatForDef = (def: Definition): string[] => {
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

    const def = schema.definitions.find(def => isInsideRange(params.position, def.defSpan));

    if (!def) {
      return { contents: [] };
    }

    if (isInsideLineRange(params.position, def.keywordSpan)) {
      return { contents: KEYWORD_DOCS[def.kind.toLowerCase()] };
    }

    if (isInsideLineRange(params.position, def.nameSpan)) {
      return { contents: formatForDef(def), range: def.nameSpan };
    }

    let target: Field | undefined;

    if (isInsideFieldsDefinition(params.position, def.fieldsSpan)) {
      for (const field of def.fields) {
        if (isInsideTypeReference(params.position, field.typeSpan)) {
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
}
