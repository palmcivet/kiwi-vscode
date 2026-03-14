<p align="center" style="text-align: center">
  <img width="300" src="./assets/brand-logo.png" alt="Kiwi VSCode brand logo" />
</p>

# Kiwi VSCode

[![Test](https://github.com/palmcivet/kiwi-vscode/actions/workflows/test.yaml/badge.svg)](https://github.com/palmcivet/kiwi-vscode/actions/workflows/test.yaml)[![GitHub Release](https://img.shields.io/github/v/release/palmcivet/kiwi-vscode)](https://github.com/palmcivet/kiwi-vscode/releases/latest)[![License](https://img.shields.io/github/license/palmcivet/kiwi-vscode?label=License)](./LICENSE.md)

English | [简体中文](./README.zh-CN.md)

> Better support for the Kiwi message format in Visual Studio Code.

Forked from [connorskees/kiwi-lsp](https://github.com/connorskees/kiwi-lsp), which published on [VSCode Marketplace](https://marketplace.visualstudio.com/items?itemName=connorskees.kiwi-lsp), identified by `connorskees.kiwi-lsp`.

## Table of Contents

- [Kiwi VSCode](#kiwi-vscode)
  - [Table of Contents](#table-of-contents)
  - [Basic Features](#basic-features)
  - [Code Formatting](#code-formatting)
  - [`@include` Syntax](#include-syntax)
    - [Motivation](#motivation)
    - [Syntax Specification](#syntax-specification)
    - [Plugin Adaptation](#plugin-adaptation)
    - [Test Data](#test-data)
  - [Build Optimization](#build-optimization)
  - [Documentation](#documentation)
  - [Logo Design](#logo-design)
  - [Credits](#credits)
  - [License](#license)

## Basic Features

The original plugin provides the following features:

- TextMate-based syntax highlighting
- Basic language configuration (including comments, bracket matching, etc.)
- Code intelligence
  - Go to definition
  - Go to references
  - Auto-completion
  - Find all references
  - Code Lens support
  - Hover documentation
  - Basic code checking
- Quick fixes
  - Auto-correct case errors
  - Generate next available ID for messages (especially useful for large messages with hundreds of fields)
- Code formatting (Beta)
  - Built on [Prettier](https://prettier.io/) with a custom plugin (`prettier-plugin-kiwi`)
  - Uses [tree-sitter](https://tree-sitter.github.io/tree-sitter/) for parsing
  - Follows Protobuf-style formatting conventions
- Automatic update checking
  - Checks for new versions from GitHub Releases on activation
  - Can be triggered manually via `Kiwi: Check for Updates` command

## Code Formatting

This extension includes a built-in code formatter for `.kiwi` files, implemented as a Prettier plugin (`prettier-plugin-kiwi`) powered by a tree-sitter grammar (`tree-sitter-kiwi`). The formatter normalizes whitespace, blank lines, comments, and quote styles to produce consistent, Protobuf-style output.

For the full formatting specification, see [Kiwi Formatting Specification](./docs/1-kiwi-grammar.md).

## `@include` Syntax

### Motivation

The original plugin's code analysis functionality was limited to the currently open file. When cross-file references existed (e.g., `derived.kiwi` referencing types from `enum.kiwi`, `base-1.kiwi`, and `base-2.kiwi`), the existing functionality couldn't properly support this usage, resulting in code checking errors.

To address this, this plugin introduces a syntax that uses `/// @include filename.kiwi` at the beginning of the file to include other kiwi files. Example:

```kiwi
/// @include ../enum.kiwi
/// @include "./base-1.kiwi"
/// @include './base-2.kiwi'
```

### Syntax Specification

- Must be placed at the beginning of the content, ignoring whitespace characters like line breaks. Can have multiple lines, but placing it elsewhere is invalid (treated as comments)
  - Valid

    ```kiwi

    /// @include ../enum.kiwi     // Valid

    /// @include "./base-1.kiwi"  // Valid with empty line
    ```

  - Invalid

    ```kiwi
    message Rect {}

    /// @include './base-1.kiwi'  // Invalid, because there's content before
    message Vector {}
    ```

- Must start with `/// @include `
- File paths support both absolute and relative paths
- Filenames can be wrapped in `''` or `""`, or without quotes
- Filenames are case-sensitive
- Multiple inclusions are imported only once, similar to `#pragma once`

### Plugin Adaptation

To adapt this syntax, the project implements the following features on top of the original plugin:

1. Clicking on `@include` files enables jumping to the corresponding file
2. When opening a `.kiwi` file, the plugin parses valid `@include` directives, concatenates dependent file contents to the current file for parsing, effectively declaring all dependencies in the current file
3. `@include` directives only affect file parsing, content concatenation only occurs during parsing, warnings and errors still correspond to the current file
4. Code Actions: Unaffected, providing correct suggestions
5. Go to Definition: Clicking on types enables jumping to the corresponding code in the original file
6. Auto-completion: After supporting `@include` directives, types from referenced files are added to the candidate list

### Test Data

See the `fixtures/intellisense/` directory, which contains test data for the language service.

The dependency relationships in the `intellisense/` folder are as follows: `package/derived.kiwi` depends on `enum.kiwi`, `package/base-1.kiwi`, and `package/base-2.kiwi`. `derived.kiwi` uses types from `enum.kiwi`, `base-1.kiwi`, and `base-2.kiwi`. During parsing, the content of the three dependent files is added to the beginning of `derived.kiwi`.

```
enum.kiwi              \
package/base-1.kiwi ----> package/derived.kiwi
package/base-2.kiwi    /
```

## Build Optimization

The original project only used `tsc` to compile code without a bundler. When packaging the plugin with `vsce`, the unoptimized output contained 590 files totaling ~760KB.

This project implements build optimizations:

1. Uses `tsup` as the build tool
2. Uses `pnpm workspace` to manage `server/` and `client/` modules

## Documentation

- [Kiwi Formatting Specification](./docs/1-kiwi-grammar.md) - Canonical formatting rules for Kiwi source files
- [Formatter Technical Documentation](./docs/2-formatter-spec.md) - Architecture and implementation details of the Prettier plugin

## Logo Design

The Logo was generated by [Slea.ai](https://slea.ai/) using the following prompt:

> a vector logo design, with the text "Kiwi", main symbol: messages, binary, code, programming language, the background is circular, minimalistic, be used in Internet industry, clear background.

## Credits

- [Cursor](https://www.cursor.com/)
- [Trae](https://www.trae.ai/)

## License

[MIT](./LICENSE.md)
