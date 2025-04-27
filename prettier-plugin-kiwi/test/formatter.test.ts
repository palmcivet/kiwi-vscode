import { strict as assert } from 'node:assert';
import { format, readTestFixture } from './utils';

describe('formatter', () => {
  it('should format comments correctly', async () => {
    const sourceCode = readTestFixture('comment.kiwi');
    const expected = readTestFixture('comment-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format enums correctly', async () => {
    const sourceCode = readTestFixture('enum.kiwi');
    const expected = readTestFixture('enum-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format includes correctly', async () => {
    const sourceCode = readTestFixture('include.kiwi');
    const expected = readTestFixture('include-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format messages correctly', async () => {
    const sourceCode = readTestFixture('message.kiwi');
    const expected = readTestFixture('message-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format space correctly', async () => {
    const sourceCode = readTestFixture('space.kiwi');
    const expected = readTestFixture('space-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format style correctly', async () => {
    const sourceCode = readTestFixture('style.kiwi');
    const expected = readTestFixture('style-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });

  it('should format syntax correctly', async () => {
    const sourceCode = readTestFixture('syntax.kiwi');
    const expected = readTestFixture('syntax-fmt.kiwi');
    const formattedCode = await format(sourceCode);
    assert.strictEqual(formattedCode, expected);
  });
});
