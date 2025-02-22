import type { Options } from 'tsup';
import * as process from 'node:process';
import { glob } from 'glob';
import { defineConfig } from 'tsup';

const SRC_CONFIG: Options = {
  entry: ['src/server.ts'],
  external: ['node:fs', 'node:path'],
  noExternal: ['change-case', 'vscode-languageserver', 'vscode-languageserver-textdocument'],
  format: 'cjs',
  outDir: './out',
};

const TEST_CONFIG: Options = {
  entry: await glob('test/**/*.test.ts', { cwd: __dirname }),
  external: ['node:fs', 'node:path', 'node:assert'],
  format: 'cjs',
  outDir: './out',
};

export default defineConfig(
  process.env.PRODUCTION ? [SRC_CONFIG] : [SRC_CONFIG, TEST_CONFIG],
);
