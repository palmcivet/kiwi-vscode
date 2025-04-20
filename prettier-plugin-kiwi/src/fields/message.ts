import type { AstPath, Doc } from 'prettier';
import type { PrettierOptions } from '../options';
import type { KiwiSyntaxNode } from '../parsers';
import { doc } from 'prettier';
import { formatComment, indentifier, isInlineComment, processBlockContent } from './utils';

const { group, indent, join, hardline } = doc.builders;

export function messageDeclaration(
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

  return group(['message ', name, ' ', body]);
}

export function messageBody(
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

    if (child.type === 'message_field') {
      const fieldDoc = childPath.call(printChildren);
      fields.push(fieldDoc);
    }
    else if (child.type === 'comment') {
      const commentDoc = formatComment(child, previousChild);
      if (previousChild && isInlineComment(child, previousChild)) {
        // 如果是行内注释，将其合并到前一个字段中
        const lastField = fields.pop()!;
        fields.push([lastField, commentDoc]);
      }
      else {
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

export function messageField(
  path: AstPath<KiwiSyntaxNode>,
  _options: PrettierOptions,
  _printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;
  const { children } = node;
  if (children.length < 5) {
    return '';
  }

  const typeNode = node.childForFieldName('message_field_type');
  const nameNode = node.childForFieldName('message_field_name');
  const valueNode = node.childForFieldName('message_field_value');

  // TODO use alias type name
  const isArray = node.descendantsOfType('[]').length > 0;
  const isDeprecated = children.some(child => child.type === 'deprecated_tag');

  const type = indentifier(typeNode) + (isArray ? '[]' : '');
  const value = indentifier(valueNode) + (isDeprecated ? ' [deprecated]' : '');

  return group([type, ' ', indentifier(nameNode), ' = ', value, ';']);
}
