import type { Doc } from 'prettier';
import type { PrettierOptions } from '../options';
import type { KiwiSyntaxNode } from '../parsers';
import { doc } from 'prettier';

const { hardline, join } = doc.builders;

export function indentifier(node: KiwiSyntaxNode | null): Doc {
  return node ? node.text : '';
}

export function isInlineComment(
  comment: KiwiSyntaxNode,
  previousNode: KiwiSyntaxNode,
): boolean {
  return (
    comment.type === 'comment' &&
    comment.startPosition.row === previousNode.endPosition.row
  );
}

export function formatComment(
  comment: KiwiSyntaxNode,
  previousNode?: KiwiSyntaxNode,
): Doc {
  const text = comment.text.replace(/^\/\/\s*/, '// ');
  if (previousNode && isInlineComment(comment, previousNode)) {
    return [' ', text];
  }
  return text;
}

/**
 * @description Get the first child with the given type name
 */
export function childForTypeName(
  node: KiwiSyntaxNode,
  typeName: string,
): KiwiSyntaxNode | null {
  const children = node.children || [];
  for (const child of children) {
    if (child.type === typeName) {
      return child;
    }
  }
  return null;
}

function isEmptyLine(doc: Doc): boolean {
  if (doc === hardline) return true;
  if (typeof doc === 'string' && /^\s*$/.test(doc)) return true;
  return false;
}

export function processBlockContent(
  docs: Doc[],
  options: PrettierOptions,
): Doc[] {
  if (!options.trimTrailingWhitespace) {
    return docs;
  }

  const result: Doc[] = [];
  let consecutiveEmptyLines = 0;

  for (const doc of docs) {
    if (isEmptyLine(doc)) {
      consecutiveEmptyLines++;
      if (consecutiveEmptyLines <= 1) {
        result.push(doc);
      }
    } else {
      consecutiveEmptyLines = 0;
      result.push(doc);
    }
  }

  return result;
}

export function processDoc(doc: Doc, options: PrettierOptions): Doc {
  if (!options.trimTrailingWhitespace) {
    return doc;
  }

  if (typeof doc === 'string') {
    return doc.replace(/[ \t]+$/gm, '');
  }

  if (Array.isArray(doc)) {
    const result: Doc[] = [];
    let consecutiveEmptyLines = 0;

    for (const item of doc) {
      if (isEmptyLine(item)) {
        consecutiveEmptyLines++;
        if (consecutiveEmptyLines === 1) {
          result.push(item);
        }
      } else {
        consecutiveEmptyLines = 0;
        result.push(processDoc(item, options));
      }
    }

    if (result.length > 0 && !isEmptyLine(result[result.length - 1])) {
      result.push(hardline);
    }

    return result;
  }

  return doc;
}

/**
 * @description 组装文档
 */
export function composeDocument(docs: Doc, options: PrettierOptions): Doc {
  if (!Array.isArray(docs)) {
    return docs;
  }

  // 在每个区块之间添加换行

  // 相邻区块

  return processDoc(join(hardline, docs), options);
}
