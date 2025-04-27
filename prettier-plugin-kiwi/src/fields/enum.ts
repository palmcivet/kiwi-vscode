import type { AstPath, Doc } from 'prettier';
import type { PrettierOptions } from '../options';
import type { KiwiSyntaxNode } from '../parsers';
import { doc } from 'prettier';
import {
  childForTypeName,
  formatComment,
  indentifier,
  isInlineComment,
  processBlockContent,
} from './utils';

const { group, indent, hardline, join } = doc.builders;

export function enumDeclaration(
  path: AstPath<KiwiSyntaxNode>,
  options: PrettierOptions,
  printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { children } = path.node;
  if (children.length < 3) {
    return '';
  }

  const childrenDocs = path.map(printChildren, 'children');
  const name = childrenDocs[1];
  const body = childrenDocs[2];

  return group(['enum ', name, ' ', body]);
}

export function enumBody(
  path: AstPath<KiwiSyntaxNode>,
  options: PrettierOptions,
  printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  if (!path.node.children?.length) {
    return '{}';
  }

  const fields: Doc[] = [];

  path.each((childPath) => {
    const { node: child } = childPath;
    const previousChild = childPath.previous as KiwiSyntaxNode;

    if (child.type === 'enum_field') {
      const fieldDoc = childPath.call(printChildren);
      fields.push(fieldDoc);
    } else if (child.type === 'comment') {
      const commentDoc = formatComment(child, previousChild);
      if (previousChild && isInlineComment(child, previousChild)) {
        const lastField = fields.pop()!;
        fields.push([lastField, commentDoc]);
      } else {
        fields.push(commentDoc);
      }
    }
  }, 'children');

  const docs = processBlockContent(fields.filter(Boolean), options);
  return group([
    '{',
    indent([hardline, join(hardline, docs)]),
    hardline,
    '}',
    hardline,
  ]);
}

export function enumField(
  path: AstPath<KiwiSyntaxNode>,
  _options: PrettierOptions,
  _printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;
  if (node.children.length < 4) {
    return '';
  }

  const nameNode = childForTypeName(node, 'enum_field_name');
  const valueNode = childForTypeName(node, 'enum_field_value');

  return group([indentifier(nameNode), ' = ', indentifier(valueNode), ';']);
}
