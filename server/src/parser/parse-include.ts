import type { Range } from 'vscode-languageserver/node';
import { readFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';

/**
 * Represents a parsed \@include directive in a kiwi file
 */
interface IncludeDirective {
  /** The raw path string extracted from the include directive */
  path: string;
  /** The full range in the document where this include directive appears */
  range: Range;
  /** The range of just the path portion within the include directive */
  pathRange: Range;
}

/**
 * Parses \@include directives from the start of a kiwi file.
 * Only processes directives that appear at the beginning of the file,
 * stopping at the first non-include content.
 *
 * @param text - The content of the kiwi file to parse
 * @returns Array of parsed include directives with their positions
 */
export function parseIncludes(text: string): IncludeDirective[] {
  const includes: IncludeDirective[] = [];
  const lines = text.split('\n');
  const parsedPaths = new Set<string>();

  // Only parse from the start of the file until we hit non-whitespace/non-include content
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i].trim();

    // Skip empty lines
    if (!line)
      continue;

    // Check for include directive
    const match = line.match(/^\/\/\/\s@include\s(['"]?)([^'"]+)\1$/);
    if (!match) {
      // Hit non-include content, stop parsing
      break;
    }

    const [fullMatch, , path] = match;
    // Skip if this path has already been included
    if (parsedPaths.has(path))
      continue;

    parsedPaths.add(path);
    const startChar = lines[i].indexOf(fullMatch);
    const pathStart = lines[i].indexOf(path, startChar);

    includes.push({
      path,
      range: {
        start: { line: i, character: startChar },
        end: { line: i, character: startChar + fullMatch.length },
      },
      pathRange: {
        start: { line: i, character: pathStart },
        end: { line: i, character: pathStart + path.length },
      },
    });
  }

  return includes;
}

/**
 * Interface for tracking file content position information in the merged content
 */
export interface FilePosition {
  /** The file path */
  filePath: string;
  /** The starting line number in the merged content */
  startLine: number;
  /** The total number of lines in the file */
  lineCount: number;
}

/**
 * Reads and processes a kiwi file and its dependencies recursively.
 * Handles file inclusion directives and maintains position mapping information.
 *
 * @param filePath - The absolute path to the kiwi file to read
 * @param visitedFiles - Set of already visited files to prevent circular dependencies
 * @returns Object containing:
 *   - `content`: The merged content of the file and all its included dependencies
 *   - `filePositions`: Array of FilePosition objects tracking the location of each file in the merged content
 */
export function readKiwiFile(filePath: string, visitedFiles: Set<string> = new Set()): {
  content: string;
  filePositions: FilePosition[];
} {
  // Prevent circular dependencies by tracking visited files
  if (visitedFiles.has(filePath)) {
    return { content: '', filePositions: [] };
  }
  visitedFiles.add(filePath);

  try {
    const content = readFileSync(filePath, 'utf8');
    const includes = parseIncludes(content);
    let currentLine = 0;
    const filePositions: FilePosition[] = [];

    // Process all included files recursively
    const includedResults = includes.map((include) => {
      const includePath = resolve(dirname(filePath), include.path);
      return readKiwiFile(includePath, visitedFiles);
    });

    // Track position information for included files
    for (const result of includedResults) {
      if (result.content) {
        filePositions.push(...result.filePositions.map(pos => ({
          ...pos,
          startLine: pos.startLine + currentLine,
        })));
        currentLine += result.content.split('\n').length;
      }
    }

    // Process current file content
    const lines = content.split('\n');
    const includeLines = new Set(includes.map(inc => inc.range.start.line));

    // Create new content array, preserving empty lines for include directives
    const contentLines = lines.map((line, index) =>
      includeLines.has(index) ? '' : line,
    );

    // Record position information for current file
    filePositions.push({
      filePath,
      startLine: currentLine,
      lineCount: lines.length, // Use original line count including include directives
    });

    // Merge all content
    const finalContent = [
      ...includedResults.map(r => r.content),
      contentLines.join('\n'),
    ].join('\n');

    return { content: finalContent, filePositions };
  }
  catch (error) {
    // TODO handle error
    console.error(`Error reading kiwi file ${filePath}: ${error}`);
    return { content: '', filePositions: [] };
  }
}

/**
 * Determines if a line position belongs to the specified file in the merged content.
 * Used to filter diagnostics and other operations to only affect the relevant file.
 *
 * @param position - The line number in the merged content to check
 * @param filePath - The absolute path of the file to check against
 * @param filePositions - Array of FilePosition objects mapping files to their locations in the merged content
 * @returns `true` if the position is within the specified file's content range, `false` otherwise
 */
export function isPositionInFile(
  position: number,
  filePath: string,
  filePositions: FilePosition[],
): boolean {
  const filePos = filePositions.find(pos => pos.filePath === filePath);
  if (!filePos)
    return false;

  return position >= filePos.startLine
    && position < filePos.startLine + filePos.lineCount;
}

/**
 * Converts a line position from the merged content back to its original file position.
 * Essential for mapping diagnostics, hover information, and other language features
 * back to their correct locations in individual files.
 *
 * @param position - The line number in the merged content to convert
 * @param filePath - The absolute path of the file to convert the position for
 * @param filePositions - Array of FilePosition objects mapping files to their locations in the merged content
 * @returns The converted line number in the original file, or the original position if conversion fails
 */
export function convertPosition(
  position: number,
  filePath: string,
  filePositions: FilePosition[],
): number {
  const filePos = filePositions.find(pos => pos.filePath === filePath);
  if (!filePos) {
    return position;
  }

  // Check if the position is within the file's content range
  if (position < filePos.startLine || position >= filePos.startLine + filePos.lineCount) {
    return position;
  }

  return position - filePos.startLine;
}

const fileUriPrefix = 'file://';

/**
 * Converts a file URI to a file path by removing the `file://` prefix if present.
 * Used to normalize file paths when processing workspace files.
 *
 * @param uri - The URI to convert (e.g., `file:///path/to/file` or `/path/to/file`)
 * @returns The file path without the `file://` prefix
 */
export function fileUriToPath(uri: string): string {
  return uri.startsWith(fileUriPrefix) ? uri.slice(fileUriPrefix.length) : uri;
}

/**
 * Converts a file path to a URI by adding the `file://` prefix.
 * Used to normalize file paths when processing workspace files.
 *
 * @param path - The file path to convert to URI
 * @returns The URI with `file://` prefix
 */
export function pathToFileUri(path: string): string {
  return path.startsWith(fileUriPrefix) ? path : `${fileUriPrefix}${path}`;
}
