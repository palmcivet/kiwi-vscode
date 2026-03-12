# Kiwi Formatter Technical Documentation

This document describes the architecture and implementation details of the Kiwi language formatter, built as a Prettier plugin using tree-sitter for parsing.

## Architecture Overview

The formatter follows Prettier's plugin architecture and consists of three layers:

```
Source Code (.kiwi)
       |
       v
  [ Parser ]          parsers.ts    tree-sitter-kiwi parses source into AST
       |
       v
  [ Printer ]         printers.ts   Traverses AST, emits Prettier Doc IR
       |
       v
  Formatted Output                  Prettier converts Doc IR to final string
```

**Key files:**

| File                                    | Role                                                    |
| --------------------------------------- | ------------------------------------------------------- |
| `prettier-plugin-kiwi/src/parsers.ts`   | Tree-sitter parser integration and AST type definitions |
| `prettier-plugin-kiwi/src/printers.ts`  | Core formatting logic                                   |
| `prettier-plugin-kiwi/src/options.ts`   | Plugin option declarations                              |
| `prettier-plugin-kiwi/src/languages.ts` | Language registration for `.kiwi` files                 |
| `tree-sitter-kiwi/grammar.js`           | Tree-sitter grammar defining the Kiwi language          |

## AST Structure

### How tree-sitter Produces the AST

The parser (`parsers.ts`) creates a tree-sitter `Parser` instance, configures it with the Kiwi grammar, and parses the input text. The resulting `tree.rootNode` (a `source_file` node) is returned as the AST for Prettier to format.

### Node Types

All named AST node types are enumerated in the `KiwiSyntaxNodeType` union type. The full list:

```
source_file, include_directive, comment, package_declaration,
enum_declaration, enum_body, enum_field, enum_field_name, enum_field_value,
message_declaration, message_body, message_field,
message_field_type, message_field_name, message_field_value,
struct_declaration, struct_body, struct_field,
struct_field_type, struct_field_name,
deprecated_tag, identifier, array, number, path, type_name
```

### Named vs Anonymous Children

Tree-sitter nodes have two kinds of children:

- **Named children** (`node.namedChildren`): Nodes with explicit type names like `identifier`, `enum_field`, etc.
- **Anonymous children** (`node.children` minus named): Literal tokens like `{`, `}`, `;`, `=`, keyword strings (`package`, `enum`, `message`, `struct`), and primitive type keywords (`bool`, `int`, `string`, etc.).

This distinction is critical for two scenarios:

1. **Comments are `extras`**: In the grammar, `comment` is listed in `extras`, so comments appear in `node.children` but NOT in the grammar rule's own `namedChildren` sequence. Any node that needs to process comments must iterate `node.children`.

2. **Primitive types are anonymous**: `type_name` is defined as `seq(choice($._primitive_type, $.identifier), optional($.array))`. Since `_primitive_type` is a hidden rule (underscore prefix), primitive type tokens like `bool`, `int`, `string` appear as anonymous children. The `printTypeName` function must iterate `children` (not `namedChildren`) to correctly reconstruct the type text.

### Example AST

For this input:

```kiwi
message User {
  int id = 1; // user id
  string name = 2;
}
```

The AST looks like:

```
source_file
  message_declaration
    "message" [anonymous]
    identifier: "User"
    message_body
      "{" [anonymous]
      message_field
        message_field_type
          type_name
            identifier: "int"    (note: "int" matches identifier, not _primitive_type)
        message_field_name
          identifier: "id"
        "=" [anonymous]
        message_field_value
          number: "1"
        ";" [anonymous]
      comment: "// user id"       <-- comment is an extra, child of message_body
      message_field
        message_field_type
          type_name
            identifier: "string"
        message_field_name
          identifier: "name"
        "=" [anonymous]
        message_field_value
          number: "2"
        ";" [anonymous]
      "}" [anonymous]
```

### Include Directive Parsing

The grammar defines `include_directive` as:

```js
include_directive: ($) => seq('/// @include ', $.path);
```

The literal prefix `'/// @include '` (with trailing space) must match exactly. This means:

- `/// @include basic.kiwi` -- parsed as `include_directive` (path = `basic.kiwi`)
- `/// @include "types.kiwi"` -- parsed as `include_directive` (path = `"types.kiwi"`)
- `///@include 'common.kiwi'` -- NOT an `include_directive` (missing space after `///`), parsed as a `comment`
- `/// @include"types.kiwi"` -- NOT an `include_directive` (missing space before path), parsed as a `comment`

Malformed include-like lines remain plain `comment` nodes and go through comment formatting rules, not include formatting.

## Formatting Rules

### Comment Normalization

The `formatCommentText` function normalizes comment spacing after `//`:

| Input         | Output         | Explanation                                |
| ------------- | -------------- | ------------------------------------------ |
| `//comment`   | `// comment`   | Insert space after `//`                    |
| `//  comment` | `// comment`   | Collapse multiple spaces to one            |
| `///comment`  | `// /comment`  | `//` + space + rest (rest starts with `/`) |
| `/// comment` | `// / comment` | `//` + space + trimmed rest                |
| `////comment` | `// //comment` | `//` + space + rest (rest is `//comment`)  |

Algorithm:

1. If the text does not start with `//`, return unchanged.
2. Take the substring after the first `//` (the "remainder").
3. If the remainder is empty, return `//`.
4. If the remainder starts with whitespace, return `// ` + the remainder with leading whitespace trimmed.
5. Otherwise return `// ` + the remainder as-is.

This preserves extra slashes (like `///` becoming `// /`) while normalizing whitespace.

### Include Directive Formatting

For real `include_directive` AST nodes, the path is normalized to double-quoted form:

| Input                       | Output                      |
| --------------------------- | --------------------------- |
| `/// @include basic.kiwi`   | `/// @include "basic.kiwi"` |
| `/// @include 'types.kiwi'` | `/// @include "types.kiwi"` |
| `/// @include "base.kiwi"`  | `/// @include "base.kiwi"`  |

The `formatIncludePath` function strips any surrounding single or double quotes, then wraps in double quotes.

### Field Formatting

Fields are reconstructed from their named children with normalized spacing:

**Enum field**: `NAME = VALUE;`

```
CREATED = 0;
```

**Message field**: `type name = number;` or `type name = number [deprecated];`

```
int id = 1;
int oldField = 1 [deprecated];
string[] names = 2;
```

**Struct field**: `type name;`

```
float x;
```

Spacing rules:

- Exactly one space around `=`
- No space before `;`
- Exactly one space before `[deprecated]`
- No space between type name and `[]` array suffix

### Package Declaration Formatting

Normalized to: `package Name;` -- one space after keyword, no space before semicolon.

### Declaration Formatting

Declarations (`enum`, `message`, `struct`) follow this pattern:

**Non-empty body:**

```kiwi
keyword Name {
  ...body...
}
```

**Empty body** (no fields, no comments):

```kiwi
keyword Name {}
```

The opening brace stays on the same line as the declaration. Body contents are indented by 2 spaces (controlled by Prettier's `tabWidth` option).

## Blank Line Rules

Blank line handling differs between the top level (`source_file`) and body contexts (`enum_body`, `message_body`, `struct_body`).

### Top Level (source_file)

- Multiple consecutive blank lines are collapsed to a single blank line.
- A single blank line between any two top-level elements is preserved.
- If there was no blank line between two elements, they remain consecutive.

Examples:

```kiwi
// Input                          // Output
// comment                        // comment



message Foo {}                    message Foo {}

message Bar {}                    message Bar {}
```

Three blank lines between the comment and `Foo` collapse to one. One blank line between `Foo` and `Bar` is preserved.

### Inside Bodies

- Blank lines between consecutive fields are always **removed**.
- Blank lines before a **standalone comment** are **preserved** (collapsed to at most one).
- Blank lines between a standalone comment and the field after it are removed.

Example:

```kiwi
// Input                          // Output
message Doc {                     message Doc {
  int id = 1;                       int id = 1;
                                     string title = 2;
  string title = 2;
                                     // Deprecated fields
                                     int old = 3;
  // Deprecated fields             }
  int old = 3;
}
```

The blank line between `id` and `title` (both fields) is removed. The blank line before the `// Deprecated fields` comment is preserved.

## Comment Attachment

Comments can appear in two roles: **inline** (attached to a preceding element on the same line) or **standalone** (on their own line).

### Inline Comment Detection

A comment is attached as inline to the previous logical item when ALL of these are true:

1. There is a previous logical item in the current container.
2. The previous item is NOT itself a comment.
3. The previous item does not already have an inline comment attached.
4. The comment is on the same source row as the previous item's end.

When attached, the output is: `<item> // comment` (single space before `//`).

### Comment After Opening Brace

A comment that appears immediately after `{` on the same line is NOT treated as an inline comment of the brace. Instead, it becomes the first standalone body item:

```kiwi
// Input                          // Output
message Logger {//Comment         message Logger {
  int level = 1;                    // Comment
}                                   int level = 1;
                                  }
```

This works because `processContainerChildren` skips brace tokens before processing. The comment after `{` has no preceding logical item, so it becomes standalone.

### Continuation Comments

A comment on the line after an inline comment is a separate standalone comment:

```kiwi
// Input                          // Output
int param1 = 4; // first line     int param1 = 4; // first line
                // continuation   // continuation
```

The `// continuation` is on a different row from `param1`, so it cannot attach as inline.

## Printer Architecture

### The `print` Function

The main `print` function is a dispatcher based on `node.type`:

```
print(path, options, print)
  |
  +-- source_file       --> printSourceFile
  +-- comment            --> formatCommentText
  +-- include_directive  --> printIncludeDirective
  +-- package_declaration --> printPackageDeclaration
  +-- *_declaration      --> printDeclaration
  +-- *_body             --> printBody
  +-- enum_field         --> printEnumField
  +-- message_field      --> printMessageField
  +-- struct_field       --> printStructField
  +-- *_field_type / type_name --> printTypeName
  +-- identifier / number / array / deprecated_tag / path --> node.text
  +-- anonymous tokens   --> node.text
```

### Two Modes of AST Traversal

The printer uses two deliberate modes of traversal:

**1. Manual `node.children` iteration** -- for containers (`source_file`, `*_body`) that need layout-aware handling of comments and blank lines. The `processContainerChildren` function iterates `node.children` directly to classify each child as a standalone item, inline comment, or skippable token.

**2. `path.call(print, 'children', index)`** -- for recursive printing of individual children through Prettier's `AstPath` system. The `printChild` helper bridges between the two: given a child node found via manual iteration, it locates the child's index in `node.children` and calls `path.call(print, 'children', index)` to recursively print it.

This separation exists because Prettier requires `AstPath`-based traversal for recursive `print` calls, but tree-sitter's `extras` (comments) require manual `children` inspection for correct layout logic.

### The `processContainerChildren` Function

This is the core layout logic. It transforms a raw `node.children` array into a `ProcessedItem[]` list:

```ts
interface ProcessedItem {
  node: KiwiSyntaxNode; // The primary node (field, comment, declaration, etc.)
  inlineComment?: KiwiSyntaxNode; // An attached inline comment, if any
  preserveBlankLineBefore?: boolean; // Whether to emit an extra blank line before this item
}
```

Processing steps:

1. **Filter**: Remove anonymous brace tokens (`{`, `}`) and semicolons.
2. **Iterate** the filtered list in source order.
3. For each `comment` node:
   - Try to attach it as an inline comment to the previous item (same row, previous is not a comment, no existing inline comment).
   - If not attachable, add as a standalone item. Check blank line preservation.
4. For each non-comment node:
   - Add as a standalone item. At top level, preserve blank lines; in bodies, do not preserve blank lines before non-comment items.

The `isBody` parameter controls blank line behavior:

- `isBody = true`: Blank lines are only preserved before standalone comments; blank lines between fields are removed.
- `isBody = false` (top level): Blank lines are preserved between any two items.

### Blank Line Detection

The `hasBlankLineBetween` function compares source positions:

```ts
function hasBlankLineBetween(prev, next) {
  return next.startPosition.row - prev.endPosition.row > 1;
}
```

When checking the "previous node" for blank line detection, the function uses the inline comment's position if one is attached (since the inline comment is the actual last thing on the previous logical line):

```ts
const prevNode = prevItem.inlineComment ?? prevItem.node;
```

### Body Rendering

`printBody` returns a flat `Doc[]` array with `hardline` separators already included. Each item is preceded by a `hardline` (or double `hardline` for blank line preservation).

`printDeclaration` wraps the body docs:

```ts
group([keyword, ' ', name, ' {', indent(bodyDocs), hardline, '}']);
```

The `indent()` call applies to the entire body content (which starts with `hardline`), so Prettier indents all body items by `tabWidth` spaces.

Important: `printBody` embeds the `hardline` separators in its return value, and `printDeclaration` does NOT add additional separators. An earlier implementation had a bug where both layers added `hardline`, causing double blank lines before comments.

### Source File Rendering

`printSourceFile` processes top-level items similarly but adds its own `hardline` separators in the loop (since there is no indent wrapper). Non-empty files end with exactly one trailing `hardline` (newline).

Empty source files return an empty string.

## Prettier Integration Points

### Plugin Registration

The plugin exports four things:

| Export      | Value                                                                                       |
| ----------- | ------------------------------------------------------------------------------------------- |
| `languages` | Registers `.kiwi` file extension with parser name `kiwi`                                    |
| `parsers`   | Maps parser name `kiwi` to the tree-sitter parse function, with `astFormat: 'kiwi-ast'`     |
| `printers`  | Maps format name `kiwi-ast` to the printer with its `print` function                        |
| `options`   | Declares plugin-specific options (`alignComments`, `alignFields`, `trimTrailingWhitespace`) |

### Doc IR Primitives Used

The printer uses only three Prettier Doc builders:

| Builder        | Purpose                                                                                                   |
| -------------- | --------------------------------------------------------------------------------------------------------- |
| `hardline`     | Unconditional line break                                                                                  |
| `indent(docs)` | Increase indentation for wrapped content                                                                  |
| `group(docs)`  | Group content (used for logical grouping; no soft-wrap behavior needed since Kiwi lines are always short) |

String literals and arrays of `Doc` values are used directly for concatenation.

## Testing

### Fixture-Based Tests

Tests live in `prettier-plugin-kiwi/test/formatter.test.ts`. Each test case reads a pair of fixture files:

- `fixtures/format/<name>.kiwi` -- unformatted input
- `fixtures/format/<name>-fmt.kiwi` -- expected formatted output

The test formats the input using Prettier with the plugin and asserts strict equality with the expected output.

Test cases cover: comments, enums, includes, messages, space normalization, style normalization, and syntax (types, arrays, deprecated tags).

### Running Tests

```sh
cd prettier-plugin-kiwi
pnpm test
```

This builds the test files with `tsup` and runs them with `mocha`.
