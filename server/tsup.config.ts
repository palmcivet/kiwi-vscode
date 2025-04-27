import { defineConfig } from 'tsup';

export default defineConfig({
  entry: ['./src/server.ts'],
  external: ['node:fs', 'node:path', 'tree-sitter-kiwi'],
  noExternal: [
    'change-case',
    'prettier',
    'prettier-plugin-kiwi',
    'vscode-languageserver',
    'vscode-languageserver-textdocument',
  ],
  format: 'cjs',
  outDir: './out',
});
