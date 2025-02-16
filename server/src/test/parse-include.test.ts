import { strict as assert } from 'node:assert';
import * as fs from 'node:fs';
import * as path from 'node:path';
import {
  convertPosition,
  fileUriToPath,
  isPositionInFile,
  parseIncludes,
  pathToFileUri,
  readKiwiFile,
} from '../parser/parse-include';

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
