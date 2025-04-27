import { defineConfig } from 'tsup';

export default defineConfig({
  entry: ['./src/extension.ts'],
  external: ['vscode', 'node:path'],
  noExternal: ['vscode-languageclient'],
  format: 'cjs',
  outDir: './out',
});
