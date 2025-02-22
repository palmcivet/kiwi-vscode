import type { Schema } from '@server/parser';
import type { TextDocument } from 'vscode-languageserver-textdocument';
import type { _, RemoteConsole, TextDocuments } from 'vscode-languageserver/node';
import { readFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { parseIncludes, parseSchema } from '@server/parser';

export class FileStore {
  private readonly console: RemoteConsole & _;
  private readonly documents: TextDocuments<TextDocument>;
  private readonly schemas: Record<string, Schema>;

  constructor(console: RemoteConsole & _, documents: TextDocuments<TextDocument>) {
    this.console = console;
    this.documents = documents;
    this.schemas = {};
  }

  public getDocuments(): TextDocuments<TextDocument> {
    return this.documents;
  }

  public getTextDocument(uri: string): TextDocument | undefined {
    return this.documents.get(uri);
  }

  private setSchema(uri: string, schema: Schema): void {
    this.schemas[uri] = schema;
  }

  private getSchema(uri: string): Schema | undefined {
    return this.schemas[uri];
  }

  public loadTextSchema(uri: string): Schema | undefined {
    const document = this.documents.get(uri);
    if (!document) {
      this.console.warn(`Failed to load document for ${uri}`);
      return this.getSchema(uri);
    }

    try {
      const [parsed, _errors] = parseSchema(document!.getText());
      this.setSchema(uri, parsed);
    }
    catch {
      this.console.warn(`Failed to parse schema for ${uri}`);
    }

    return this.getSchema(uri);
  }

  public loadIncludedSchemas(filePath: string): Map<string, Schema> {
    const schemas = new Map<string, Schema>();
    const visited = new Set<string>();

    const load = (currentPath: string) => {
      if (visited.has(currentPath))
        return;
      visited.add(currentPath);

      try {
        const content = readFileSync(currentPath, 'utf8');
        const [schema, _] = parseSchema(content);
        schemas.set(currentPath, schema);

        // Recursively load included schemas
        const includes = parseIncludes(content);
        for (const include of includes) {
          const includePath = resolve(dirname(currentPath), include.path);
          load(includePath);
        }
      }
      catch (error) {
        this.console.error(`Error loading schema from ${currentPath}: ${error}`);
      }
    };

    load(filePath);
    return schemas;
  }
}
