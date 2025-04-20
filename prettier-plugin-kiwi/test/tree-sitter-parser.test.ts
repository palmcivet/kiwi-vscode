import { strict as assert } from 'node:assert';
import * as fs from 'node:fs';
import * as path from 'node:path';
import Parser from 'tree-sitter';
import Kiwi from 'tree-sitter-kiwi';
import { FIXTURES_PATH } from './utils';

describe('tree-sitter parser', () => {
  let parser: Parser;

  before(async () => {
    parser = new Parser();
    parser.setLanguage(Kiwi);
  });

  it('should parse kiwi file correctly', () => {
    const testFilePath = path.join(FIXTURES_PATH, 'space.kiwi');
    assert.ok(fs.existsSync(testFilePath), 'test file not found');

    const content = fs.readFileSync(testFilePath, 'utf8');
    const tree = parser.parse(content);

    // Basic assertions
    assert.ok(tree.rootNode, 'root node should exist');
    assert.strictEqual(tree.rootNode.type, 'source_file', 'root node should be source_file');

    // Check the children of the root node
    const rootChildren = tree.rootNode.children;
    assert.ok(rootChildren.length > 0, 'source file should have children');

    // Check the first child
    const firstChild = rootChildren[0];
    assert.ok(firstChild.type, 'node should have type');
    assert.ok(firstChild.startPosition, 'node should have start position');
    assert.ok(firstChild.endPosition, 'node should have end position');
  });

  it('should handle empty file', () => {
    const tree = parser.parse('');
    assert.ok(tree.rootNode, 'root node should exist for empty file');
    assert.strictEqual(tree.rootNode.type, 'source_file', 'root node type should be source_file');
    assert.strictEqual(tree.rootNode.children.length, 0, 'empty file should have no children');
  });

  it('should handle invalid syntax', () => {
    const tree = parser.parse('invalid { syntax }');
    assert.ok(tree.rootNode, 'root node should exist for invalid syntax');
    assert.ok(tree.rootNode.hasError, 'tree should contain error nodes for invalid syntax');
  });
});
