import { glob } from 'glob';
import { defineConfig } from 'tsup';

export default defineConfig({
  entry: await glob('**/*.test.ts'),
  external: ['node:fs', 'node:path', 'node:assert'],
  format: 'cjs',
  outDir: './out',
  sourcemap: true,
});
