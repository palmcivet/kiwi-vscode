import type { Position, Range } from 'vscode-languageserver/node';

/**
 * Combines multiple ranges into a new range.
 * The new range will include the minimum start position and maximum end position of all input ranges.
 *
 * @param ranges - Array of ranges to combine
 * @returns A new range that encompasses all input ranges
 */
export function combineRanges(...ranges: Range[]) {
  let start = { ...ranges[0].start };
  let end = { ...ranges[0].end };

  for (const r of ranges) {
    if (r.start.line < start.line) {
      start = { ...r.start };
    }
    else if (r.start.line === start.line) {
      start.character = Math.min(start.character, r.start.character);
    }

    if (r.end.line > end.line) {
      end = { ...r.end };
    }
    else if (r.end.line === end.line) {
      end.character = Math.max(end.character, r.end.character);
    }
  }

  return { start, end };
}

/**
 * Gets the end position of a range and extends it by one character.
 * Typically used when inserting new content at the end of a range.
 *
 * @param range - The range to process
 * @returns A new range with both start and end positions at the original range's end, but end character position increased by 1
 */
export function endOfRange(range: Range): Range {
  return {
    start: { line: range.end.line, character: range.end.character },
    end: { line: range.end.line, character: range.end.character + 1 },
  };
}

/**
 * Checks if a position is inside a specified range.
 * Supports multi-line ranges and considers both line numbers and character positions.
 *
 * @param position - The position to check
 * @param range - The range to check against, can be undefined
 * @returns `true` if the position is inside the range, `false` otherwise
 */
export function isInsideRange(position: Position, range: Range | undefined): boolean {
  if (!range) {
    return false;
  }

  // Return false if position is before start line or after end line
  if (position.line < range.start.line || position.line > range.end.line) {
    return false;
  }

  // Check character position if on start line
  if (position.line === range.start.line) {
    return position.character >= range.start.character;
  }

  // Check character position if on end line
  if (position.line === range.end.line) {
    return position.character <= range.end.character;
  }

  // Position is on a middle line
  return true;
}

/**
 * Checks if a position is inside a single-line range.
 * Unlike isInsideRange, this function only checks positions within the same line.
 *
 * @param position - The position to check
 * @param range - The range to check against
 * @returns `true` if the position is inside the single-line range, `false` otherwise
 */
export function isPositionInRange(position: Position, range: Range): boolean {
  if (position.line !== range.start.line) {
    return false;
  }
  return position.character >= range.start.character
    && position.character <= range.end.character;
}

/**
 * Checks if the cursor is within a type reference range.
 * Specifically for checking type references, assuming they are always on a single line.
 *
 * @param position - The cursor position to check
 * @param typeSpan - The type reference range, can be undefined
 * @returns `true` if the cursor is within the type reference range, `false` otherwise
 */
export function isInsideTypeReference(position: Position, typeSpan: Range | undefined): boolean {
  if (!typeSpan) {
    return false;
  }

  // Type references are typically on a single line
  if (position.line !== typeSpan.start.line) {
    return false;
  }

  return position.character >= typeSpan.start.character
    && position.character <= typeSpan.end.character;
}

/**
 * Checks if the cursor is within a fields definition area.
 * Uses isInsideRange to check if the position is within the fields definition range.
 *
 * @param position - The cursor position to check
 * @param fieldsSpan - The fields definition range
 * @returns `true` if the cursor is within the fields definition area, `false` otherwise
 */
export function isInsideFieldsDefinition(position: Position, fieldsSpan: Range): boolean {
  return isInsideRange(position, fieldsSpan);
}

/**
 * Checks if the cursor is within a specific position range on a single line.
 * Similar to isPositionInRange, but specifically for checking line-specific positions.
 *
 * @param position - The cursor position to check
 * @param range - The range to check against
 * @returns `true` if the cursor is within the specified line position range, `false` otherwise
 */
export function isInsideLineRange(position: Position, range: Range): boolean {
  if (position.line !== range.start.line) {
    return false;
  }
  return position.character >= range.start.character
    && position.character <= range.end.character;
}
