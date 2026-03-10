import type { AstPath, Doc, Printer } from 'prettier';
import type { PrettierOptions } from './options';
import type { KiwiSyntaxNode } from './parsers';
import { doc } from 'prettier';

const { group, indent, hardline } = doc.builders;

/**
 * @description Represents a processed logical item from a container's children,
 * with optional inline comment and blank line preservation info.
 */
interface ProcessedItem {
  node: KiwiSyntaxNode;
  inlineComment?: KiwiSyntaxNode;
  preserveBlankLineBefore?: boolean;
}

// MARK: Low-level helpers

/**
 * @description Normalize a plain comment's text.
 *
 * Rules:
 * - `//comment`    -> `// comment`
 * - `//  comment`  -> `// comment`
 * - `///comment`   -> `// /comment`
 * - `/// comment`  -> `// / comment`
 * - `////comment`  -> `// //comment`
 *
 * Practical algorithm:
 * 1. Strip the leading `//`
 * 2. If the remainder starts with whitespace, trim it and emit `// ` + trimmed
 * 3. Otherwise emit `// ` + remainder (preserving extra slashes)
 */
function formatCommentText(text: string): string {
  if (!text.startsWith('//')) {
    return text;
  }

  const remainder = text.slice(2);
  if (remainder.length === 0) {
    return '//';
  }

  if (/^\s+/.test(remainder)) {
    return `// ${remainder.trimStart()}`;
  }

  return `// ${remainder}`;
}

/**
 * @description Normalize an include path to double-quoted form.
 */
function formatIncludePath(pathNode: KiwiSyntaxNode): string {
  const unquoted = pathNode.text.replace(/^['"]|['"]$/g, '');
  return `"${unquoted}"`;
}

/**
 * @description Check whether there is at least one blank line between two nodes.
 */
function hasBlankLineBetween(
  prev: KiwiSyntaxNode,
  next: KiwiSyntaxNode,
): boolean {
  return next.startPosition.row - prev.endPosition.row > 1;
}

/**
 * @description Print a specific child node using Prettier's AstPath traversal.
 */
function printChild(
  path: AstPath<KiwiSyntaxNode>,
  print: (path: AstPath<KiwiSyntaxNode>) => Doc,
  child: KiwiSyntaxNode,
): Doc {
  const index = path.node.children.indexOf(child);
  if (index === -1) {
    return child.text;
  }
  return path.call(print, 'children', index);
}

/**
 * @description Process the children of a container node (enum_body, message_body,
 * struct_body, or source_file) into a list of logical items.
 *
 * This handles:
 * - Skipping brace tokens
 * - Detecting inline comments attached to the previous field/declaration
 * - Preserving blank lines before standalone comments
 *
 * @param children - the children array of the container node
 * @param isBody - true for body containers (enum_body, message_body, struct_body)
 */
function processContainerChildren(
  children: KiwiSyntaxNode[],
  isBody: boolean,
): ProcessedItem[] {
  const items: ProcessedItem[] = [];

  // Filter to meaningful children (skip braces and anonymous punctuation in bodies)
  const meaningful: KiwiSyntaxNode[] = [];
  for (const child of children) {
    if (!child.isNamed && (child.text === '{' || child.text === '}')) {
      continue;
    }
    // Skip semicolons and other anonymous tokens at container level
    if (!child.isNamed && child.text === ';') {
      continue;
    }
    meaningful.push(child);
  }

  let i = 0;
  while (i < meaningful.length) {
    const current = meaningful[i];

    if (current.type === 'comment') {
      // Check if this comment is an inline comment attached to the previous item
      if (items.length > 0) {
        const prevItem = items[items.length - 1];
        const prevNode = prevItem.inlineComment ?? prevItem.node;

        // Attach as inline if: same row, previous is not a comment, and no inline comment yet
        if (
          prevItem.node.type !== 'comment' &&
          !prevItem.inlineComment &&
          current.startPosition.row === prevNode.endPosition.row
        ) {
          prevItem.inlineComment = current;
          i++;
          continue;
        }
      }

      // Standalone comment - check blank line preservation
      let preserveBlank = false;
      if (items.length > 0) {
        const prevItem = items[items.length - 1];
        const prevNode = prevItem.inlineComment ?? prevItem.node;
        if (hasBlankLineBetween(prevNode, current)) {
          if (isBody) {
            // In bodies, only preserve blank lines before standalone comments
            preserveBlank = true;
          } else {
            // At top level, always preserve blank lines
            preserveBlank = true;
          }
        }
      }

      items.push({
        node: current,
        preserveBlankLineBefore: preserveBlank,
      });
    } else {
      // Non-comment node
      let preserveBlank = false;
      if (items.length > 0) {
        const prevItem = items[items.length - 1];
        const prevNode = prevItem.inlineComment ?? prevItem.node;
        if (hasBlankLineBetween(prevNode, current)) {
          if (!isBody) {
            // At top level, preserve blank lines between any items
            preserveBlank = true;
          }
          // In bodies, blank lines between fields are removed (not preserved)
        }
      }

      items.push({
        node: current,
        preserveBlankLineBefore: preserveBlank,
      });
    }

    i++;
  }

  return items;
}

// MARK: Leaf / type printers

/**
 * @description Print a type_name node. Handles both primitive types (anonymous children)
 * and identifier-based types, plus optional array suffix.
 */
function printTypeName(node: KiwiSyntaxNode): string {
  // If this is a wrapper node (message_field_type or struct_field_type),
  // unwrap to the actual type_name child
  let typeNode = node;
  if (node.type === 'message_field_type' || node.type === 'struct_field_type') {
    const inner = node.children.find((c) => c.type === 'type_name');
    if (inner) {
      typeNode = inner;
    }
  }

  let result = '';
  for (const child of typeNode.children) {
    if (child.type === 'identifier') {
      result += child.text;
    } else if (child.type === 'array') {
      result += '[]';
    } else if (!child.isNamed) {
      // Anonymous primitive type token
      result += child.text;
    }
  }
  return result;
}

/**
 * @description Print an enum field: `name = value;`
 */
function printEnumField(node: KiwiSyntaxNode): Doc {
  const nameNode = node.children.find((c) => c.type === 'enum_field_name');
  const valueNode = node.children.find((c) => c.type === 'enum_field_value');

  const name = nameNode?.text ?? '';
  const value = valueNode?.text ?? '';

  return group([name, ' = ', value, ';']);
}

/**
 * @description Print a message field: `type name = value;` or `type name = value [deprecated];`
 */
function printMessageField(node: KiwiSyntaxNode): Doc {
  const typeNode = node.children.find((c) => c.type === 'message_field_type');
  const nameNode = node.children.find((c) => c.type === 'message_field_name');
  const valueNode = node.children.find((c) => c.type === 'message_field_value');

  const typeName = typeNode ? printTypeName(typeNode) : '';
  const fieldName = nameNode?.text ?? '';

  // Extract number and optional deprecated tag from message_field_value
  let number = '';
  let hasDeprecated = false;
  if (valueNode) {
    const numNode = valueNode.children.find((c) => c.type === 'number');
    const deprecatedNode = valueNode.children.find(
      (c) => c.type === 'deprecated_tag',
    );
    number = numNode?.text ?? '';
    hasDeprecated = !!deprecatedNode;
  }

  const parts: Doc[] = [typeName, ' ', fieldName, ' = ', number];
  if (hasDeprecated) {
    parts.push(' [deprecated]');
  }
  parts.push(';');

  return group(parts);
}

/**
 * @description Print a struct field: `type name;`
 */
function printStructField(node: KiwiSyntaxNode): Doc {
  const typeNode = node.children.find((c) => c.type === 'struct_field_type');
  const nameNode = node.children.find((c) => c.type === 'struct_field_name');

  const typeName = typeNode ? printTypeName(typeNode) : '';
  const fieldName = nameNode?.text ?? '';

  return group([typeName, ' ', fieldName, ';']);
}

// MARK: Simple top-level printers

/**
 * @description Print an include directive: `/// @include "path.kiwi"`
 */
function printIncludeDirective(node: KiwiSyntaxNode): Doc {
  const pathNode = node.children.find((c) => c.type === 'path');
  if (!pathNode) {
    return node.text;
  }
  return group(['/// @include ', formatIncludePath(pathNode)]);
}

/**
 * @description Print a package declaration: `package Name;`
 */
function printPackageDeclaration(node: KiwiSyntaxNode): Doc {
  const nameNode = node.children.find((c) => c.type === 'identifier');
  if (!nameNode) {
    return node.text;
  }
  return group(['package ', nameNode.text, ';']);
}

// MARK: Container printers

/**
 * @description Print the inner contents of a body (enum_body, message_body, struct_body).
 * Returns a flat Doc array with hardline separators already included.
 * The caller wraps with indent and braces.
 */
function printBody(
  path: AstPath<KiwiSyntaxNode>,
  print: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc[] {
  const { node } = path;
  const items = processContainerChildren(node.children, true);
  const docs: Doc[] = [];

  for (let i = 0; i < items.length; i++) {
    const item = items[i];

    // Add separator before each item (hardline, or double hardline for blank line preservation)
    if (i > 0 && item.preserveBlankLineBefore) {
      docs.push(hardline);
      docs.push(hardline);
    } else {
      docs.push(hardline);
    }

    const itemDoc = printChild(path, print, item.node);
    if (item.inlineComment) {
      const commentDoc = printChild(path, print, item.inlineComment);
      docs.push(group([itemDoc, ' ', commentDoc]));
    } else {
      docs.push(itemDoc);
    }
  }

  return docs;
}

/**
 * @description Print a declaration (enum, message, or struct).
 *
 * Handles:
 * - keyword + name + body
 * - empty body -> `keyword Name {}`
 * - non-empty body -> multi-line block
 */
function printDeclaration(
  path: AstPath<KiwiSyntaxNode>,
  print: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;

  // Determine keyword from node type
  let keyword: string;
  let bodyType: string;
  switch (node.type) {
    case 'enum_declaration':
      keyword = 'enum';
      bodyType = 'enum_body';
      break;
    case 'message_declaration':
      keyword = 'message';
      bodyType = 'message_body';
      break;
    case 'struct_declaration':
      keyword = 'struct';
      bodyType = 'struct_body';
      break;
    default:
      return node.text;
  }

  const nameNode = node.children.find((c) => c.type === 'identifier');
  const bodyNode = node.children.find((c) => c.type === bodyType);

  const name = nameNode?.text ?? '';

  if (!bodyNode) {
    return group([keyword, ' ', name, ' {}']);
  }

  // Check if body is empty (no meaningful children)
  const bodyItems = processContainerChildren(bodyNode.children, true);
  if (bodyItems.length === 0) {
    return group([keyword, ' ', name, ' {}']);
  }

  // Print body contents via path traversal
  const bodyIndex = node.children.indexOf(bodyNode);
  const bodyDocs: Doc[] = path.call(
    (bodyPath) => printBody(bodyPath, print),
    'children',
    bodyIndex,
  ) as unknown as Doc[];

  // bodyDocs already contains hardline separators
  return group([keyword, ' ', name, ' {', indent(bodyDocs), hardline, '}']);
}

/**
 * @description Print the source_file node (top-level container).
 */
function printSourceFile(
  path: AstPath<KiwiSyntaxNode>,
  print: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;

  if (node.children.length === 0) {
    return '';
  }

  const items = processContainerChildren(node.children, false);
  if (items.length === 0) {
    return '';
  }

  const docs: Doc[] = [];

  for (let i = 0; i < items.length; i++) {
    const item = items[i];

    if (i > 0) {
      docs.push(hardline);
      if (item.preserveBlankLineBefore) {
        docs.push(hardline);
      }
    }

    const itemDoc = printChild(path, print, item.node);
    if (item.inlineComment) {
      const commentDoc = printChild(path, print, item.inlineComment);
      docs.push(group([itemDoc, ' ', commentDoc]));
    } else {
      docs.push(itemDoc);
    }
  }

  // End with exactly one trailing newline
  docs.push(hardline);

  return docs;
}

// MARK: Main print function

function print(
  path: AstPath<KiwiSyntaxNode>,
  options: PrettierOptions,
  print: (path: AstPath<KiwiSyntaxNode>) => Doc,
): Doc {
  const { node } = path;

  switch (node.type) {
    case 'source_file':
      return printSourceFile(path, print);

    case 'comment':
      return formatCommentText(node.text);

    case 'include_directive':
      return printIncludeDirective(node);

    case 'package_declaration':
      return printPackageDeclaration(node);

    case 'enum_declaration':
    case 'message_declaration':
    case 'struct_declaration':
      return printDeclaration(path, print);

    case 'enum_body':
    case 'message_body':
    case 'struct_body':
      return printBody(path, print);

    case 'enum_field':
      return printEnumField(node);

    case 'message_field':
      return printMessageField(node);

    case 'struct_field':
      return printStructField(node);

    case 'message_field_type':
    case 'struct_field_type':
    case 'type_name':
      return printTypeName(node);

    case 'identifier':
    case 'number':
    case 'array':
    case 'deprecated_tag':
    case 'path':
      return node.text;

    default:
      // Anonymous tokens (keywords, punctuation, etc.)
      if (!node.isNamed) {
        return node.text;
      }
      throw new Error(`Unknown node type: ${node.type}`);
  }
}

export const printers: Record<string, Printer> = {
  'kiwi-ast': {
    print,
  },
};
