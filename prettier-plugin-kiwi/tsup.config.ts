import { defineConfig } from 'tsup';

export default defineConfig({
  entry: ['./src/index.ts'],
  external: ['prettier', 'tree-sitter', 'tree-sitter-kiwi'],
  format: 'cjs',
  outDir: './out',
  dts: true,
  treeshake: true,
});
