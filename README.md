<p align="center">
  <img width="300" src="https://github.com/palmcivet/kiwi-vscode/blob/master/assets/brand-logo.png?raw=true" alt="Kiwi VSCode brand logo" />
</p>

# Kiwi VSCode

English | [简体中文](./README.zh-CN.md)

> Better support for the Kiwi message format in Visual Studio Code.

Forked from [connorskees/kiwi-lsp](https://github.com/connorskees/kiwi-lsp), which published on [VSCode Marketplace](https://marketplace.visualstudio.com/items?itemName=connorskees.kiwi-lsp), identified by `connorskees.kiwi-lsp`.

## Table of Contents

- [Kiwi VSCode](#kiwi-vscode)
  - [Table of Contents](#table-of-contents)
  - [Basic Features](#basic-features)
  - [`@include` Syntax](#include-syntax)
    - [Motivation](#motivation)
    - [Syntax Specification](#syntax-specification)
    - [Plugin Adaptation](#plugin-adaptation)
    - [Test Data](#test-data)
  - [Build Optimization](#build-optimization)
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

The original project only used `tsc` to compile code without a bundler. When packaging the plugin with `vsce`, the following prompt was received:

```bash
This extension consists of 590 files, out of which 341 are JavaScript files. For performance reasons, you should bundle your extension: https://aka.ms/vscode-bundle-extension
....
kiwi-vscode-1.0.3.vsix (590 files, 759.55KB)
```

This project implements build optimizations:

1. Uses `tsup` as the build tool
2. Uses `pnpm workspace` to manage `server/` and `client/` modules

The optimized build output is as follows:

```bash
client build: CJS out/extension.js 1.02 KB
client build: CJS ⚡️ Build success in 27ms
client build: Done
server build: CJS out/server.js 19.45 KB
server build: CJS ⚡️ Build success in 111ms
...
kiwi-vscode-1.0.3.vsix (11 files, 131.39 KB)
```

The compressed plugin package size is reduced by 80%, and the extracted files are more streamlined.

## Logo Design

The Logo was generated by [Slea.ai](https://slea.ai/) using the following prompt:

> a vector logo design, with the text "Kiwi", main symbol: Messages, binary, code, programming language, the background is circular, Minimalistic, be used in Internet industry, clear background.

## Credits

- [Cursor](https://www.cursor.com/)
- [Trae](https://www.trae.ai/)

## License

[MIT](./LICENSE.md)
