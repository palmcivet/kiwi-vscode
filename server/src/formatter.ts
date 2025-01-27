import type { TextEdit } from 'vscode-languageserver-types';
import { Position, Range } from 'vscode-languageserver-types';

export function formatKiwi(text: string): TextEdit[] {
  if (!text)
    return [];

  const lines = text.split('\n');
  const edits: TextEdit[] = [];
  let inBlock = false;
  let consecutiveEmptyLines = 0;

  // 处理每一行
  for (let i = 0; i < lines.length; i++) {
    let line = lines[i];
    const originalLine = line;
    const trimmedLine = line.trim();

    // 1. 处理缩进
    if (trimmedLine.length > 0) {
      if (inBlock && !trimmedLine.startsWith('}')) {
        // 块内的内容缩进两个空格
        line = `  ${trimmedLine}`;
      }
      else {
        line = trimmedLine;
      }
    }

    // 2. 处理注释格式
    if (line.includes('//')) {
      const parts = line.split('//');
      const code = parts[0].trimEnd();
      const comment = parts[1].trim();
      line = `${code + (code.length > 0 ? ' ' : '')}// ${comment}`;
    }

    // 3. 处理块内外的空行
    if (trimmedLine.includes('{')) {
      inBlock = true;
      if (line.endsWith('{')) {
        line = `${line} `;
      }
    }
    else if (trimmedLine.includes('}')) {
      inBlock = false;
      consecutiveEmptyLines = 0;
    }

    if (trimmedLine === '') {
      consecutiveEmptyLines++;
      if (inBlock && consecutiveEmptyLines > 1) {
        // 块内只保留一个空行
        edits.push({
          range: Range.create(
            Position.create(i, 0),
            Position.create(i + 1, 0),
          ),
          newText: '',
        });
        continue;
      }
      else if (!inBlock && consecutiveEmptyLines > 1) {
        // 块外只保留一个空行
        edits.push({
          range: Range.create(
            Position.create(i, 0),
            Position.create(i + 1, 0),
          ),
          newText: '',
        });
        continue;
      }
    }
    else {
      consecutiveEmptyLines = 0;
    }

    // 如果当前行需要修改
    if (line !== originalLine) {
      edits.push({
        range: Range.create(
          Position.create(i, 0),
          Position.create(i, originalLine.length),
        ),
        newText: line,
      });
    }
  }

  // 4. 处理文件末尾空行
  let lastNonEmptyLine = lines.length - 1;
  while (lastNonEmptyLine >= 0 && lines[lastNonEmptyLine].trim() === '') {
    lastNonEmptyLine--;
  }

  if (lastNonEmptyLine < lines.length - 1) {
    edits.push({
      range: Range.create(
        Position.create(lastNonEmptyLine + 1, 0),
        Position.create(lines.length, 0),
      ),
      newText: '\n',
    });
  }

  return edits;
}
