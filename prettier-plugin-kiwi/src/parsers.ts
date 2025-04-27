import type { Parser } from 'prettier';
import TreeSitter from 'tree-sitter';
import Kiwi from 'tree-sitter-kiwi';

type KiwiSyntaxNodeType =
  | 'source_file'
  | 'include_directive'
  | 'comment'
  | 'package_declaration'
  | 'enum_declaration'
  | 'enum_body'
  | 'enum_field'
  | 'enum_field_name'
  | 'enum_field_value'
  | 'message_declaration'
  | 'message_body'
  | 'message_field'
  | 'message_field_type'
  | 'message_field_name'
  | 'message_field_value'
  | 'struct_declaration'
  | 'struct_body'
  | 'struct_field'
  | 'struct_field_type'
  | 'struct_field_name'
  | 'deprecated_tag'
  | 'identifier'
  | 'array';

export interface KiwiSyntaxNode extends TreeSitter.SyntaxNode {
  type: KiwiSyntaxNodeType;
  children: Array<KiwiSyntaxNode>;
}

function parse(text: string): KiwiSyntaxNode {
  const treeSitter = new TreeSitter();
  treeSitter.setLanguage(Kiwi);

  const tree = treeSitter.parse(text);
  if (tree.rootNode.hasError) {
    throw new Error(`Parsing error: ${tree.rootNode}`);
  }

  return tree.rootNode as KiwiSyntaxNode;
}

function locStart(node: KiwiSyntaxNode): number {
  return node.startIndex;
}

function locEnd(node: KiwiSyntaxNode): number {
  return node.endIndex;
}

export const parsers: Record<string, Parser> = {
  kiwi: {
    astFormat: 'kiwi-ast',
    parse,
    locStart,
    locEnd,
  },
};
