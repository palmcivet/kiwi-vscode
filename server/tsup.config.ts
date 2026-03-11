import { defineConfig } from 'tsup';

export default defineConfig({
  entry: ['./src/server.ts'],
  external: [
    'node:fs',
    'node:path',
    'prettier',
    'prettier-plugin-kiwi',
    'tree-sitter',
    'tree-sitter-kiwi',
  ],
  noExternal: [
    'change-case',
    'vscode-languageserver',
    'vscode-languageserver-textdocument',
  ],
  format: 'cjs',
  outDir: './out',
  treeshake: true,
});
