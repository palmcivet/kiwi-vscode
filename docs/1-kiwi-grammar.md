# Kiwi Formatting Specification

This document defines the canonical formatting style for Kiwi language source files. The goal of the formatter is to transform any valid Kiwi source code into a consistent style that conforms to this specification.

- [Kiwi Formatting Specification](#kiwi-formatting-specification)
  - [1. File Structure](#1-file-structure)
  - [2. Indentation](#2-indentation)
  - [3. Whitespace Rules](#3-whitespace-rules)
    - [3.1 Assignment Operator](#31-assignment-operator)
    - [3.2 Semicolons](#32-semicolons)
    - [3.3 Deprecated Marker](#33-deprecated-marker)
    - [3.4 Type and Field Name](#34-type-and-field-name)
    - [3.5 Array Marker](#35-array-marker)
    - [3.6 Declaration Keywords](#36-declaration-keywords)
    - [3.7 Opening Brace](#37-opening-brace)
  - [4. Blank Line Rules](#4-blank-line-rules)
    - [4.1 Top-Level Blank Lines](#41-top-level-blank-lines)
    - [4.2 Blank Lines Inside Declaration Bodies](#42-blank-lines-inside-declaration-bodies)
  - [5. Comments](#5-comments)
    - [5.1 Comment Spacing](#51-comment-spacing)
    - [5.2 Multi-Slash Comments](#52-multi-slash-comments)
    - [5.3 Inline Comments](#53-inline-comments)
    - [5.4 Comments After Opening Braces](#54-comments-after-opening-braces)
    - [5.5 Standalone Comments](#55-standalone-comments)
    - [5.6 Continuation Comments](#56-continuation-comments)
  - [6. `package` Declaration](#6-package-declaration)
  - [7. `include` Directive](#7-include-directive)
    - [7.1 Invalid `include` Syntax](#71-invalid-include-syntax)
  - [8. `enum` Declarations](#8-enum-declarations)
    - [8.1 Field Format](#81-field-format)
    - [8.2 Empty Enum](#82-empty-enum)
  - [9. `message` Declarations](#9-message-declarations)
    - [9.1 Field Format](#91-field-format)
    - [9.2 Empty Message](#92-empty-message)
  - [10. `struct` Declarations](#10-struct-declarations)
    - [10.1 Field Format](#101-field-format)
    - [10.2 Empty Struct](#102-empty-struct)
  - [11. Type System](#11-type-system)
    - [11.1 Primitive Types](#111-primitive-types)
    - [11.2 Custom Types](#112-custom-types)
    - [11.3 Array Types](#113-array-types)
  - [12. Comprehensive Example](#12-comprehensive-example)

## 1. File Structure

A Kiwi file consists of the following sections in order. Each section is optional:

```kiwi
[package declaration]
[include directives]
[type declarations (enum / message / struct)]
```

Files must end with exactly one newline character. Empty files produce no output.

## 2. Indentation

* Indentation uses spaces.
* The default indentation width is **2 spaces**.
* Content inside declaration bodies (`{` and `}`) is indented by one level.
* Top-level elements are not indented.

## 3. Whitespace Rules

### 3.1 Assignment Operator

Exactly one space appears on both sides of `=`:

```kiwi
int id = 1;
ACTIVE = 0;
```

### 3.2 Semicolons

`;` appears immediately after the value or `[deprecated]`, with **no preceding space**:

```kiwi
int id = 1;
int old = 2 [deprecated];
float x;
```

### 3.3 Deprecated Marker

`[deprecated]` is preceded by exactly one space, separating it from the value:

```kiwi
int oldField = 1 [deprecated];
```

### 3.4 Type and Field Name

Exactly one space appears between the type name and the field name:

```kiwi
int id = 1;
string[] names = 2;
User author = 3;
```

### 3.5 Array Marker

`[]` appears immediately after the type name, with no intervening space:

```kiwi
int[] numbers = 1;
string[] names = 2;
User[] users = 3;
```

### 3.6 Declaration Keywords

Declaration keywords (`package`, `enum`, `message`, `struct`) are followed by exactly one space before the name:

```kiwi
package Example;
enum Status { ... }
message User { ... }
struct Point { ... }
```

### 3.7 Opening Brace

`{` is preceded by exactly one space after the declaration name and always appears on the same line as the declaration (K&R style):

```kiwi
message User {
  ...
}
```

## 4. Blank Line Rules

### 4.1 Top-Level Blank Lines

Blank lines between top-level elements (package declarations, include directives, type declarations, or standalone comments):

* Existing blank lines in the source are **preserved**.
* Multiple consecutive blank lines are **collapsed into a single blank line**.
* If no blank line exists between two top-level elements in the source, the formatter **does not insert one**.

Example: three blank lines collapse into one, and an existing blank line between `Foo` and `Bar` is preserved.

### 4.2 Blank Lines Inside Declaration Bodies

Inside declaration bodies (`enum_body`, `message_body`, `struct_body`):

* Blank lines **between fields are removed**.
* Blank lines **before standalone comments are preserved** (multiple lines collapse to one).
* Blank lines **after standalone comments and before the next field are removed**.

Example:

```kiwi
// Input                        // Output
message Doc {                  message Doc {
  int id = 1;                    int id = 1;
                                 string title = 2;
  string title = 2;
                                 // Section
                                 int old = 3;
  // Section                   }
  int old = 3;
}
```

The blank line between `id` and `title` is removed (two fields).
The blank line before the `// Section` comment is preserved.

## 5. Comments

Kiwi supports only `//` single-line comments.

### 5.1 Comment Spacing

Exactly one space follows `//`. Extra spaces are collapsed.

| Input              | Output            |
| ------------------ | ----------------- |
| `//comment`        | `// comment`      |
| `//  extra spaces` | `// extra spaces` |
| `//`               | `//`              |

### 5.2 Multi-Slash Comments

Additional slashes after `//` are treated as part of the comment content.

Normalization rule: insert one space after the first two slashes (`//`), and preserve the remaining content unchanged.

| Input         | Output         | Explanation                |
| ------------- | -------------- | -------------------------- |
| `///comment`  | `// /comment`  | `//` + space + `/comment`  |
| `/// comment` | `// / comment` | `//` + space + `/ comment` |
| `////comment` | `// //comment` | `//` + space + `//comment` |

Note: `/// @include` is the syntax prefix for include directives and is **not** treated as a regular comment. This rule does not apply to it.

### 5.3 Inline Comments

Comments that appear at the end of the same line as a field, declaration, or directive are considered **inline comments**. After formatting, exactly one space separates the preceding content and the comment.

```kiwi
int id = 1; // user id
package Example; // package name
/// @include "types.kiwi" // note
```

A comment is considered inline if:

* It appears on the same line as the preceding element in the source.
* The preceding element is not another comment.
* The preceding element is not an opening brace `{`.

### 5.4 Comments After Opening Braces

Comments appearing immediately after `{` on the same line are **not treated as inline comments**. Instead, they become the first standalone comment inside the declaration body.

```kiwi
// Input                        // Output
message Logger {//Comment      message Logger {
  int level = 1;                 // Comment
}                                int level = 1;
                               }
```

### 5.5 Standalone Comments

Comments that do not share a line with a preceding element are treated as standalone comments. They occupy their own line and follow the indentation of the surrounding context.

```kiwi
message User {
  // Field group
  int id = 1;
  // Another group
  string name = 2;
}
```

### 5.6 Continuation Comments

A standalone comment appearing on the line after a field’s inline comment is treated as an independent comment and is **not merged** with the inline comment.

```kiwi
int param = 4; // first line
// second line
int other = 5;
```

## 6. `package` Declaration

Format: `package Name;`

Rules:

* One space follows the `package` keyword.
* The name is immediately followed by `;` with no preceding space.
* Extra spaces are removed.

```kiwi
// Input                        // Output
package    Example   ;         package Example;
```

## 7. `include` Directive

Format:

```kiwi
/// @include "path"
```

Rules:

* Paths must be enclosed in double quotes.
* Paths written with single quotes or without quotes are converted to double quotes.

| Input                       | Output                      |
| --------------------------- | --------------------------- |
| `/// @include basic.kiwi`   | `/// @include "basic.kiwi"` |
| `/// @include 'types.kiwi'` | `/// @include "types.kiwi"` |
| `/// @include "base.kiwi"`  | `/// @include "base.kiwi"`  |

### 7.1 Invalid `include` Syntax

The exact syntax prefix for include directives is:

```
/// @include
```

(note the trailing space)

Content that does not match this pattern is parsed as a regular comment and formatted according to comment rules.

| Input                       | Parsed As | Output                       |
| --------------------------- | --------- | ---------------------------- |
| `///@include 'common.kiwi'` | comment   | `// /@include 'common.kiwi'` |
| `/// @include"types.kiwi"`  | comment   | `// / @include"types.kiwi"`  |

## 8. `enum` Declarations

```kiwi
enum Name {
  FIELD_A = 0;
  FIELD_B = 1;
}
```

### 8.1 Field Format

```kiwi
NAME = VALUE;
```

Rules:

* One space around `=`.
* `;` appears immediately after the value with no preceding space.

### 8.2 Empty Enum

An enum with no fields and no comments is formatted on a single line:

```kiwi
enum Empty {}
```

## 9. `message` Declarations

```kiwi
message Name {
  type fieldName = number;
  type fieldName = number [deprecated];
}
```

### 9.1 Field Format

```kiwi
type name = number;
type name = number [deprecated];
```

Rules:

* One space between type, name, `=`, and the numeric identifier.
* `[deprecated]` is optional and preceded by one space when present.
* `;` appears immediately after the final element.

### 9.2 Empty Message

```kiwi
message Empty {}
```

## 10. `struct` Declarations

```kiwi
struct Name {
  type fieldName;
}
```

### 10.1 Field Format

```kiwi
type name;
```

Rules:

* One space between the type and the field name.
* `;` appears immediately after the name.
* Struct fields do not have numeric identifiers or deprecated markers.

### 10.2 Empty Struct

```kiwi
struct Empty {}
```

## 11. Type System

### 11.1 Primitive Types

Kiwi supports the following primitive types:

```
bool, byte, int32, int64, uint32, uint64, float, double, string
```

Note: shorthand types such as `int` and `uint` are parsed as `identifier` tokens and are treated the same as custom types.

### 11.2 Custom Types

Fields may reference previously declared `enum`, `message`, or `struct` types.

```kiwi
message User {
  Role role = 1;
  Settings settings = 2;
}
```

### 11.3 Array Types

Arrays are declared by appending `[]` to the type name. The brackets must appear immediately after the type name without spaces.

Both primitive and custom types can be used as arrays.

```kiwi
int[] numbers = 1;
string[] names = 2;
User[] users = 3;
```

Kiwi does not support multidimensional arrays.

## 12. Comprehensive Example

Before formatting:

```kiwi
// 空格和空行
package    Example   ;

/// @include     "base.kiwi"
/// @include   'types.kiwi'



message Empty{




}

message    Spaced    {
  int    id   =    1;
  string     name    =2;   // trailing comment
}

// 注释对齐
enum Status {
  ACTIVE = 1;   // active status
  DELETED = 2;     // deleted status
  ARCHIVED = 3;// archived status
}
```

After formatting:

```kiwi
// 空格和空行
package Example;

/// @include "base.kiwi"
/// @include "types.kiwi"

message Empty {}

message Spaced {
  int id = 1;
  string name = 2; // trailing comment
}

// 注释对齐
enum Status {
  ACTIVE = 1; // active status
  DELETED = 2; // deleted status
  ARCHIVED = 3; // archived status
}
```
