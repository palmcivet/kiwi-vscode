import { defineConfig } from 'tsup';

export default defineConfig({
  entry: ['./src/index.ts'],
  external: ['node:fs', 'node:path', 'tree-sitter', 'tree-sitter-kiwi'],
  format: 'cjs',
  outDir: './out',
  dts: true,
});
