import * as fs from 'node:fs';
import * as path from 'node:path';
import prettier from 'prettier';
import * as plugin from '../src';

export const FIXTURES_PATH = path.join(__dirname, '../../fixtures/format');

export function readTestFixture(filename: string): string {
  const testFile = path.join(FIXTURES_PATH, filename);
  return fs.readFileSync(testFile, 'utf-8');
}

export async function format(text: string): Promise<string> {
  return await prettier.format(text, {
    parser: 'kiwi',
    plugins: [plugin],
    tabWidth: 2,
    useTabs: false,
  });
}
