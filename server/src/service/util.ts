import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { _, _Connection, Position, TextDocuments } from 'vscode-languageserver/node';
import type { Definition, Schema } from '../parser/schema';
import { readFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { isInsideRange } from '../helper';
import { parseIncludes, parseSchema } from '../parser';
import { store } from './store';

export type ServerConnection = _Connection<_, _, _, _, _, _, _, _>;

export function getSchema(uri: string, documents: TextDocuments<TextDocument>): Schema | undefined {
  try {
    const document = documents.get(uri);
    const [parsed, _errors] = parseSchema(document!.getText());
    store.setFile(uri, parsed);
  }
  catch {
    //
  }

  return store.getFile(uri);
}

/**
 * 递归加载文件的所有依赖
 */
export function loadIncludedSchemas(filePath: string): Map<string, Schema> {
  const schemas = new Map<string, Schema>();
  const visited = new Set<string>();

  function load(currentPath: string) {
    if (visited.has(currentPath))
      return;
    visited.add(currentPath);

    try {
      const content = readFileSync(currentPath, 'utf8');
      const [schema, _] = parseSchema(content);
      schemas.set(currentPath, schema);

      // 处理该文件的 includes
      const includes = parseIncludes(content);
      for (const include of includes) {
        const includePath = resolve(dirname(currentPath), include.path);
        load(includePath);
      }
    }
    catch (error) {
      // TODO handle error
      console.error(`Error loading schema from ${currentPath}: ${error}`);
    }
  }

  load(filePath);
  return schemas;
}

export function findContainingDefinition(
  position: Position,
  schema: Schema,
): Definition | undefined {
  return schema.definitions.find(def => isInsideRange(position, def.defSpan));
}
