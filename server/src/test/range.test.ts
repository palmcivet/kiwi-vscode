import { strict as assert } from 'node:assert';
import {
  combineRanges,
  endOfRange,
  isInsideFieldsDefinition,
  isInsideLineRange,
  isInsideRange,
  isInsideTypeReference,
  isPositionInRange,
} from '../helper';

describe('range utilities', () => {
  describe('combineRanges', () => {
    it('should combine ranges on the same line', () => {
      const range1 = { start: { line: 0, character: 0 }, end: { line: 0, character: 5 } };
      const range2 = { start: { line: 0, character: 3 }, end: { line: 0, character: 8 } };
      const combined = combineRanges(range1, range2);
      assert.deepStrictEqual(combined, {
        start: { line: 0, character: 0 },
        end: { line: 0, character: 8 },
      });
    });

    it('should combine ranges on different lines', () => {
      const range1 = { start: { line: 0, character: 0 }, end: { line: 1, character: 5 } };
      const range2 = { start: { line: 2, character: 3 }, end: { line: 3, character: 8 } };
      const combined = combineRanges(range1, range2);
      assert.deepStrictEqual(combined, {
        start: { line: 0, character: 0 },
        end: { line: 3, character: 8 },
      });
    });
  });

  describe('endOfRange', () => {
    it('should create a single-character range at the end', () => {
      const range = { start: { line: 1, character: 0 }, end: { line: 1, character: 5 } };
      const result = endOfRange(range);
      assert.deepStrictEqual(result, {
        start: { line: 1, character: 5 },
        end: { line: 1, character: 6 },
      });
    });
  });

  describe('isInsideRange', () => {
    const range = {
      start: { line: 1, character: 5 },
      end: { line: 3, character: 10 },
    };

    it('should return false for undefined range', () => {
      const position = { line: 2, character: 7 };
      assert.strictEqual(isInsideRange(position, undefined), false);
    });

    it('should return true for position within range', () => {
      const position = { line: 2, character: 7 };
      assert.strictEqual(isInsideRange(position, range), true);
    });

    it('should return true for position at start line with valid character', () => {
      const position = { line: 1, character: 6 };
      assert.strictEqual(isInsideRange(position, range), true);
    });

    it('should return false for position before range', () => {
      const position = { line: 0, character: 0 };
      assert.strictEqual(isInsideRange(position, range), false);
    });
  });

  describe('isPositionInRange', () => {
    const range = {
      start: { line: 1, character: 5 },
      end: { line: 1, character: 10 },
    };

    it('should return true for position on same line within range', () => {
      const position = { line: 1, character: 7 };
      assert.strictEqual(isPositionInRange(position, range), true);
    });

    it('should return false for position on different line', () => {
      const position = { line: 2, character: 7 };
      assert.strictEqual(isPositionInRange(position, range), false);
    });
  });

  describe('isInsideTypeReference', () => {
    it('should return false for undefined typeSpan', () => {
      const position = { line: 1, character: 5 };
      assert.strictEqual(isInsideTypeReference(position, undefined), false);
    });

    it('should return true for position within type reference', () => {
      const typeSpan = {
        start: { line: 1, character: 5 },
        end: { line: 1, character: 10 },
      };
      const position = { line: 1, character: 7 };
      assert.strictEqual(isInsideTypeReference(position, typeSpan), true);
    });
  });

  describe('isInsideFieldsDefinition', () => {
    const fieldsSpan = {
      start: { line: 1, character: 0 },
      end: { line: 3, character: 10 },
    };

    it('should return true for position within fields definition', () => {
      const position = { line: 2, character: 5 };
      assert.strictEqual(isInsideFieldsDefinition(position, fieldsSpan), true);
    });

    it('should return false for position outside fields definition', () => {
      const position = { line: 0, character: 5 };
      assert.strictEqual(isInsideFieldsDefinition(position, fieldsSpan), false);
    });
  });

  describe('isInsideLineRange', () => {
    const range = {
      start: { line: 1, character: 5 },
      end: { line: 1, character: 10 },
    };

    it('should return true for position within line range', () => {
      const position = { line: 1, character: 7 };
      assert.strictEqual(isInsideLineRange(position, range), true);
    });

    it('should return false for position on different line', () => {
      const position = { line: 2, character: 7 };
      assert.strictEqual(isInsideLineRange(position, range), false);
    });
  });
});
