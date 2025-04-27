import type { AstPath, Doc, Printer } from 'prettier';
import type { PrettierOptions } from './options';
import type { KiwiSyntaxNode } from './parsers';
import { doc } from 'prettier';
import {
  composeDocument,
  enumBody,
  enumDeclaration,
  enumField,
  formatComment,
  indentifier,
  messageBody,
  messageDeclaration,
  messageField,
  structBody,
  structDeclaration,
  structField,
} from './fields';

const { group } = doc.builders;

function print(
  path: AstPath<KiwiSyntaxNode>,
  options: PrettierOptions,
  printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;

  switch (node.type) {
    case 'source_file': {
      const definitions = path.map((childPath) => {
        return childPath.call(printChildren);
      }, 'children');
      return composeDocument(definitions.filter(Boolean), options);
    }

    case 'comment': {
      const parentNode = path.getParentNode() as KiwiSyntaxNode;
      const { previous } = path;
      const previousNode =
        previous &&
        ['source_file', 'enum_body', 'message_body', 'struct_body'].includes(
          parentNode?.type,
        )
          ? previous
          : undefined;
      return formatComment(node, previousNode);
    }

    case 'include_directive': {
      const { children } = node;
      if (children.length < 2) {
        return '';
      }
      return group(['/// @include ', children[1].text]);
    }

    case 'package_declaration': {
      const { children } = node;
      if (children.length < 2) {
        return '';
      }
      const packageName = path.map(printChildren, 'children')[1];
      return group(['package ', packageName, ';']);
    }

    case 'enum_declaration':
      return enumDeclaration(path, options, printChildren);

    case 'enum_body':
      return enumBody(path, options, printChildren);

    case 'enum_field':
      return enumField(path, options, printChildren);

    case 'message_declaration':
      return messageDeclaration(path, options, printChildren);

    case 'message_body':
      return messageBody(path, options, printChildren);

    case 'message_field':
      return messageField(path, options, printChildren);

    case 'struct_declaration':
      return structDeclaration(path, options, printChildren);

    case 'struct_body':
      return structBody(path, options, printChildren);

    case 'struct_field':
      return structField(path, options, printChildren);

    case 'identifier':
      return indentifier(node);

    default:
      return '';
  }
}

export const printers: Record<string, Printer> = {
  'kiwi-ast': {
    print,
  },
};
