import type { AstPath, Doc, Printer } from 'prettier';
import type { PrettierOptions } from './options';
import type { KiwiSyntaxNode } from './parsers';
import { doc } from 'prettier';

const { group } = doc.builders;

function print(
  path: AstPath<KiwiSyntaxNode>,
  options: PrettierOptions,
  printChildren: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;

  switch (node.type) {
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

    default:
      return '';
  }
}

export const printers: Record<string, Printer> = {
  'kiwi-ast': {
    print,
  },
};
