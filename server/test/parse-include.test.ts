import type { TextDocument } from 'vscode-languageserver-textdocument';
import { strict as assert } from 'node:assert';
import * as fs from 'node:fs';
import * as path from 'node:path';
import {
  convertPosition,
  fileUriToPath,
  isPositionInFile,
  parseIncludes,
  pathToFileUri,
  processKiwiContent,
  readKiwiDocument,
  readKiwiFile,
} from '@server/parser';

describe('parse include utilities', () => {
  describe('parseIncludes', () => {
    it('should handle file with no includes', () => {
      const input = 'message Test {}\n';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should parse single include directive', () => {
      const input = '/// @include \'common.kiwi\'\nmessage Test {}\n';
      const includes = parseIncludes(input);

      assert.strictEqual(includes.length, 1);
      assert.strictEqual(includes[0].path, 'common.kiwi');
      assert.deepStrictEqual(includes[0].range, {
        start: { line: 0, character: 0 },
        end: { line: 0, character: 26 },
      });
    });

    it('should parse multiple include directives', () => {
      const input = '/// @include "common.kiwi"\n/// @include "types.kiwi"\n\nmessage Test {}\n';
      const includes = parseIncludes(input);

      assert.strictEqual(includes.length, 2);
      assert.strictEqual(includes[1].path, 'types.kiwi');
    });

    it('should handle empty lines between includes', () => {
      const input = '/// @include "common.kiwi"\n\n/// @include "types.kiwi"\n';
      const includes = parseIncludes(input);

      assert.strictEqual(includes.length, 2);
    });

    it('should handle empty lines before includes', () => {
      const input = '\n /// @include "common.kiwi"\n\n/// @include "types.kiwi"\n';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 2);
    });

    it('should handle spaces before includes', () => {
      const input = '  /// @include "common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 1);
    });

    it('should handle include directives without quotes', () => {
      const input = '/// @include ../common.kiwi\nmessage Test {}';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 1);
      assert.strictEqual(includes[0].path, '../common.kiwi');
    });

    it('should handle absolute paths', () => {
      const input = '/// @include "/absolute/path/common.kiwi"\nmessage Test {}';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 1);
      assert.strictEqual(includes[0].path, '/absolute/path/common.kiwi');
    });

    it('should ignore include directives after content', () => {
      const input = 'message Test {}\n/// @include "common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore include directives after comment', () => {
      const input = '// comment\n/// @include "common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore duplicate include directives', () => {
      const input = '/// @include "common.kiwi"\n/// @include "common.kiwi"\nmessage Test {}';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 1);
    });

    it('should not parse include directives with //', () => {
      const input = '// @include "common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore include directives with extra spaces', () => {
      const input = '///   @include   "common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore include directives with invalid format', () => {
      const input = '///@include"common.kiwi"';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore include directives with mixed quotes', () => {
      const input = '/// @include "common.kiwi\'';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });

    it('should ignore include directives with incomplete path', () => {
      const input = '/// @include ';
      const includes = parseIncludes(input);
      assert.strictEqual(includes.length, 0);
    });
  });

  describe('processKiwiContent', () => {
    const testDir = path.join(__dirname, 'fixtures');
    const mainFile = path.join(testDir, 'main.kiwi');
    const commonFile = path.join(testDir, 'common.kiwi');

    beforeEach(() => {
      if (!fs.existsSync(testDir)) {
        fs.mkdirSync(testDir, { recursive: true });
      }
      fs.writeFileSync(commonFile, 'message Common {\n  field1: string;\n}\n');
      fs.writeFileSync(mainFile, '/// @include "common.kiwi"\nmessage Main {\n  field2: int32;\n}\n');
    });

    afterEach(() => {
      if (fs.existsSync(testDir)) {
        fs.rmSync(testDir, { recursive: true, force: true });
      }
    });

    it('should process content with includes correctly', () => {
      const content = fs.readFileSync(mainFile, 'utf8');
      const result = processKiwiContent(content, mainFile, new Set());

      assert.ok(result.content.includes('message Common'));
      assert.ok(result.content.includes('message Main'));
      assert.strictEqual(result.filePositions.length, 2);
      assert.strictEqual(result.filePositions[1].filePath, mainFile);
    });

    it('should handle content without includes', () => {
      const content = 'message Test {\n  field: string;\n}\n';
      const result = processKiwiContent(content, mainFile, new Set());

      assert.strictEqual(result.filePositions.length, 1);
      assert.strictEqual(result.content, content);
    });

    it('should preserve line numbers in merged content', () => {
      const content = '/// @include "common.kiwi"\n\nmessage Main {\n  field2: int32;\n}\n';
      const result = processKiwiContent(content, mainFile, new Set());

      const lines = result.content.split('\n');
      assert.ok(lines.includes(''));
      assert.ok(result.content.includes('message Common'));
      assert.ok(result.content.includes('message Main'));
    });
  });

  describe('readKiwiFile', () => {
    const testDir = path.join(__dirname, 'fixtures');
    const mainFile = path.join(testDir, 'main.kiwi');
    const commonFile = path.join(testDir, 'common.kiwi');

    beforeEach(() => {
      // Create test directory and files
      if (!fs.existsSync(testDir)) {
        fs.mkdirSync(testDir, { recursive: true });
      }

      fs.writeFileSync(commonFile, 'message Common {}\n');
      fs.writeFileSync(mainFile, '/// @include "common.kiwi"\nmessage Main {}\n');
    });

    afterEach(() => {
      // Cleanup test files
      if (fs.existsSync(testDir)) {
        fs.rmSync(testDir, { recursive: true, force: true });
      }
    });

    it('should read and merge included files', () => {
      const result = readKiwiFile(mainFile);

      assert.strictEqual(result.filePositions.length, 2);
      assert.ok(result.content.includes('message Common'));
      assert.ok(result.content.includes('message Main'));
    });

    it('should handle circular dependencies', () => {
      fs.writeFileSync(mainFile, '/// @include "circular.kiwi"\nmessage Main {}\n');
      fs.writeFileSync(path.join(testDir, 'circular.kiwi'), '/// @include "main.kiwi"\nmessage Circular {}\n');

      const result = readKiwiFile(mainFile);
      assert.ok(result.content.includes('message Main'));
    });
  });

  describe('readKiwiDocument', () => {
    const testDir = path.join(__dirname, 'fixtures');
    const mainFile = path.join(testDir, 'main.kiwi');

    beforeEach(() => {
      if (!fs.existsSync(testDir)) {
        fs.mkdirSync(testDir, { recursive: true });
      }
    });

    afterEach(() => {
      if (fs.existsSync(testDir)) {
        fs.rmSync(testDir, { recursive: true, force: true });
      }
    });

    it('should process TextDocument content correctly', () => {
      const uri = pathToFileUri(mainFile);
      const content = '/// @include "common.kiwi"\nmessage Main {}\n';
      const document = {
        uri,
        getText: () => content,
      } as TextDocument;

      const result = readKiwiDocument(document);
      assert.ok(result.filePositions.length > 0);
      assert.strictEqual(result.filePositions[0].filePath, mainFile);
    });

    it('should handle circular dependencies in TextDocument', () => {
      const uri = pathToFileUri(mainFile);
      const content = '/// @include "main.kiwi"\nmessage Main {}\n';
      const document = {
        uri,
        getText: () => content,
      } as TextDocument;

      const visitedFiles = new Set([mainFile]);
      const result = readKiwiDocument(document, visitedFiles);

      assert.strictEqual(result.content, '');
      assert.strictEqual(result.filePositions.length, 0);
    });

    it('should handle errors gracefully', () => {
      const uri = pathToFileUri(mainFile);
      const document = {
        uri,
        getText: (): string => { throw new Error('Failed to read document'); },
      } as TextDocument;

      const result = readKiwiDocument(document);
      assert.strictEqual(result.content, '');
      assert.strictEqual(result.filePositions.length, 0);
    });
  });

  describe('isPositionInFile', () => {
    it('should return true for position within file range', () => {
      const filePositions = [{
        filePath: '/test/file.kiwi',
        startLine: 10,
        lineCount: 5,
      }];

      assert.strictEqual(isPositionInFile(12, '/test/file.kiwi', filePositions), true);
    });

    it('should return false for position outside file range', () => {
      const filePositions = [{
        filePath: '/test/file.kiwi',
        startLine: 10,
        lineCount: 5,
      }];

      assert.strictEqual(isPositionInFile(16, '/test/file.kiwi', filePositions), false);
    });
  });

  describe('convertPosition', () => {
    it('should convert position within file range', () => {
      const filePositions = [{
        filePath: '/test/file.kiwi',
        startLine: 10,
        lineCount: 5,
      }];

      assert.strictEqual(convertPosition(12, '/test/file.kiwi', filePositions), 2);
    });

    it('should return original position for position outside file range', () => {
      const filePositions = [{
        filePath: '/test/file.kiwi',
        startLine: 10,
        lineCount: 5,
      }];

      assert.strictEqual(convertPosition(16, '/test/file.kiwi', filePositions), 16);
    });
  });

  describe('fileUriToPath', () => {
    it('should convert file URI to path', () => {
      const uri = 'file:///test/file.kiwi';
      assert.strictEqual(fileUriToPath(uri), '/test/file.kiwi');
    });

    it('should return original path for non-file URI', () => {
      const path = '/test/file.kiwi';
      assert.strictEqual(fileUriToPath(path), path);
    });
  });

  describe('pathToFileUri', () => {
    it('should convert path to file URI', () => {
      const path = '/test/file.kiwi';
      assert.strictEqual(pathToFileUri(path), 'file:///test/file.kiwi');
    });

    it('should return original URI for non-path', () => {
      const uri = 'file:///test/file.kiwi';
      assert.strictEqual(pathToFileUri(uri), uri);
    });
  });
});
