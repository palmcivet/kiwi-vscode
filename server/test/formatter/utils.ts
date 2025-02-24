import * as fs from 'node:fs';
import * as path from 'node:path';

export const FIXTURES_PATH = path.join(__dirname, '../../../fixtures/format');

export function readTestFixture(filename: string): string {
  const testFile = path.join(FIXTURES_PATH, filename);
  return fs.readFileSync(testFile, 'utf-8');
}
