import type { Options } from 'tsup';
import * as process from 'node:process';
import { glob } from 'glob';
import { defineConfig } from 'tsup';

const SRC_CONFIG: Options = {
  entry: ['src/extension.ts'],
  external: ['vscode', 'node:path'],
  noExternal: ['vscode-languageclient'],
  format: 'cjs',
  outDir: './out',
};

const TEST_CONFIG: Options = {
  entry: await glob('test/**/*.test.ts', { cwd: __dirname }),
  external: ['vscode', 'mocha', 'node:path'],
  format: 'cjs',
  outDir: './out',
};

export default defineConfig(
  process.env.PRODUCTION ? [SRC_CONFIG] : [SRC_CONFIG, TEST_CONFIG],
);
