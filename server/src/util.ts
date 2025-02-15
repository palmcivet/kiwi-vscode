import type { Position, Range } from 'vscode-languageserver';
import * as fs from 'fs';
import * as path from 'path';

export function quote(text: string): string {
  return JSON.stringify(text);
}

type ErrorKind = 'invalid id';

export class KiwiParseError extends Error {
  constructor(
    message: string,
    public readonly range: Range,
    public readonly relatedInformation?: RelatedInformation,
    public readonly errorKind?: ErrorKind,
  ) {
    super(message);
  }
}

interface RelatedInformation {
  span: Range;
  message: string;
}

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

export function endOfRange(range: Range): Range {
  return {
    start: { line: range.end.line, character: range.end.character },
    end: { line: range.end.line, character: range.end.character + 1 },
  };
}

// export function error(text: string, line: number, column: number): never;
export function error(
  text: string,
  range: Range,
  relatedInformation?: RelatedInformation,
): never {
  throw new KiwiParseError(text, range, relatedInformation);
}

export function createError(
  text: string,
  range: Range,
  relatedInformation?: RelatedInformation,
  errorKind?: ErrorKind,
): KiwiParseError {
  return new KiwiParseError(text, range, relatedInformation, errorKind);
}

export function isPascalCase(s: string): boolean {
  return s[0] >= 'A' && s[0] <= 'Z' && !s.includes('_');
}

export function isCamelCase(s: string): boolean {
  return s[0] >= 'a' && s[0] <= 'z' && !s.includes('_');
}

export function isScreamingSnakeCase(s: string): boolean {
  if (!(s[0] >= 'A' && s[0] <= 'Z')) {
    return false;
  }

  for (const c of s) {
    if ((c >= 'A' && c <= 'Z') || c === '_' || (c >= '0' && c <= '9')) {
      continue;
    }

    return false;
  }

  return true;
}

/**
 * 判断一个位置是否在范围内
 */
export function isInsideRange(position: Position, range: Range | undefined): boolean {
  if (!range) {
    return false;
  }

  // 如果位置在范围的起始行之前或结束行之后，直接返回 false
  if (position.line < range.start.line || position.line > range.end.line) {
    return false;
  }

  // 如果位置在起始行
  if (position.line === range.start.line) {
    return position.character >= range.start.character;
  }

  // 如果位置在结束行
  if (position.line === range.end.line) {
    return position.character <= range.end.character;
  }

  // 位置在范围的中间行
  return true;
}

/**
 * Represents a parsed @include directive
 */
interface IncludeDirective {
  /** The raw path string from the include directive */
  path: string;
  /** The range in the document where this include appears */
  range: Range;
  /** The range of just the path portion */
  pathRange: Range;
}

/**
 * Parses @include directives from the start of a kiwi file
 */
export function parseIncludes(text: string): IncludeDirective[] {
  const includes: IncludeDirective[] = [];
  const lines = text.split('\n');

  // Only parse from the start of the file until we hit non-whitespace/non-include content
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i].trim();

    // Skip empty lines
    if (!line) continue;

    // Check for include directive
    const match = line.match(/^\/\/\/\s*@include\s+(['"]?)([^'"]+)\1$/);
    if (!match) {
      // Hit non-include content, stop parsing
      break;
    }

    const [fullMatch, , path] = match;
    const startChar = lines[i].indexOf(fullMatch);
    const pathStart = lines[i].indexOf(path, startChar);

    includes.push({
      path,
      range: {
        start: { line: i, character: startChar },
        end: { line: i, character: startChar + fullMatch.length }
      },
      pathRange: {
        start: { line: i, character: pathStart },
        end: { line: i, character: pathStart + path.length }
      }
    });
  }

  return includes;
}

// 添加新的接口来跟踪文件内容的位置信息
interface FilePosition {
  /** 文件路径 */
  filePath: string;
  /** 在合并内容中的起始行 */
  startLine: number;
  /** 文件的行数 */
  lineCount: number;
}

/**
 * 读取并处理 kiwi 文件及其依赖
 */
export function readKiwiFile(filePath: string, visitedFiles: Set<string> = new Set()): {
  content: string;
  filePositions: FilePosition[];
} {
  if (visitedFiles.has(filePath)) {
    return { content: '', filePositions: [] };
  }
  visitedFiles.add(filePath);

  try {
    const content = fs.readFileSync(filePath, 'utf8');
    const includes = parseIncludes(content);
    let currentLine = 0;
    const filePositions: FilePosition[] = [];

    // 处理所有 includes
    const includedResults = includes.map(include => {
      const includePath = path.resolve(path.dirname(filePath), include.path);
      return readKiwiFile(includePath, visitedFiles);
    });

    // 记录每个包含文件的位置信息
    for (const result of includedResults) {
      if (result.content) {
        filePositions.push(...result.filePositions.map(pos => ({
          ...pos,
          startLine: pos.startLine + currentLine
        })));
        currentLine += result.content.split('\n').length;
      }
    }

    // 计算当前文件的内容
    const lines = content.split('\n');
    const includeLines = new Set(includes.map(inc => inc.range.start.line));

    // 创建一个新的内容数组，保留 include 指令的空行
    const contentLines = lines.map((line, index) =>
      includeLines.has(index) ? '' : line
    );

    // 记录当前文件的位置信息，包括所有行（包括 include 指令的行）
    filePositions.push({
      filePath,
      startLine: currentLine,
      lineCount: lines.length // 使用原始行数，包括 include 指令
    });

    // 合并所有内容
    const finalContent = [
      ...includedResults.map(r => r.content),
      contentLines.join('\n')
    ].join('\n');

    return { content: finalContent, filePositions };
  } catch (error) {
    console.error(`Error reading kiwi file ${filePath}: ${error}`);
    return { content: '', filePositions: [] };
  }
}

/**
 * 判断一个位置是否属于指定文件
 */
export function isPositionInFile(
  position: number,
  filePath: string,
  filePositions: FilePosition[]
): boolean {
  const filePos = filePositions.find(pos => pos.filePath === filePath);
  if (!filePos) return false;

  return position >= filePos.startLine &&
         position < filePos.startLine + filePos.lineCount;
}

/**
 * 将合并内容中的位置转换为原始文件中的位置
 */
export function convertPosition(
  position: number,
  filePath: string,
  filePositions: FilePosition[]
): number {
  const filePos = filePositions.find(pos => pos.filePath === filePath);
  if (!filePos) return position;

  return position - filePos.startLine;
}

/**
 * 将文件 URI 转换为文件路径
 */
export function uriToFilePath(uri: string): string {
  return uri.startsWith('file://') ? uri.slice(7) : uri;
}
