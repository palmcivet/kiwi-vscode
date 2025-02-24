<p align="center">
  <img width="300" src="https://github.com/palmcivet/kiwi-vscode/blob/master/assets/brand-logo.png?raw=true" alt="Kiwi VSCode brand logo" />
</p>

# Kiwi VSCode

[English](./README.md) | 简体中文

> 为 Visual Studio Code 提供更好的 Kiwi 消息格式支持

本项目是从 [connorskees/kiwi-lsp](https://github.com/connorskees/kiwi-lsp) 分叉而来，该项目发布在 [VSCode 插件市场](https://marketplace.visualstudio.com/items?itemName=connorskees.kiwi-lsp)，标识符为 `connorskees.kiwi-lsp`。

## 目录

- [Kiwi VSCode](#kiwi-vscode)
  - [目录](#目录)
  - [基础功能](#基础功能)
  - [`@include` 语法](#include-语法)
    - [需求背景](#需求背景)
    - [语法规范](#语法规范)
    - [插件适配](#插件适配)
    - [测试数据](#测试数据)
  - [构建优化](#构建优化)
  - [Logo 设计](#logo-设计)
  - [致谢](#致谢)
  - [协议](#协议)

## 基础功能

原始插件提供以下功能：

- 基于 TextMate 的语法高亮
- 基础语言配置（包括注释、括号匹配等）
- 代码智能提示
  - 转到定义
  - 转到引用
  - 自动补全
  - 查找所有引用
  - Code Lens 支持
  - 悬停文档提示
  - 基础代码检查
- 快速修复
  - 自动纠正大小写错误
  - 为消息生成下一个可用 ID（特别适用于包含数百个字段的大型消息）

## `@include` 语法
### 需求背景

原始插件的代码分析功能仅限于当前打开的文件。当存在跨文件引用时（例如 `derived.kiwi` 引用了 `enum.kiwi`、`base-1.kiwi`、`base-2.kiwi` 中的类型），现有功能无法正确支持这种用法，导致代码检查报错。

为此本插件设计了一种语法，在文件的开头，使用 `/// @include filename.kiwi` 来引入其他 kiwi 文件。示例如下：

```kiwi
/// @include ../enum.kiwi
/// @include "./base-1.kiwi"
/// @include './base-2.kiwi'
```

### 语法规范

- 必须放在内容的开头，忽略换行等空白字符，可以有多行，放在其他行无效（等同于注释）
  - 有效
    ```kiwi

    /// @include ../enum.kiwi     // 有效

    /// @include "./base-1.kiwi"  // 空了一行，有效
    ```
  - 无效
    ```kiwi
    message Rect {}

    /// @include './base-1.kiwi'  // 无效，因为前面有内容
    message Vector {}
    ```
- 必须以 `/// @include ` 开头
- 文件支持绝对路径和相对路径
- 文件名可使用 `''` 或 `""` 包裹，也可以不写引号
- 文件名大小写敏感
- 多次引用时只会导入一次，类似 `#pragma once`

### 插件适配

为适配该语法，在原插件的基础上，本项目实现了以下功能：

1. 点击 `@include` 的文件时能够跳转到对应文件
2. 当打开 `.kiwi` 文件时，插件会解析该文件中有效的 `@include` 指令，将依赖的文件内容拼接到当前文件合并解析，等效在当前文件声明了所有依赖的内容
3. `@include` 指令只影响文件解析，拼接文件内容只发生在解析时，警告和错误仍对应当前文件
4. Code Action：不受影响，能给出正确的建议
5. 转到定义：点击类型时能够跳转到原文件中对应的代码
6. 自动补全：在支持 `@include` 指令之后，引用文件中的类型也会加入到候选列表

### 测试数据

见 `fixtures/intellisense/` 目录，该文件夹是语言服务的测试数据。

`intellisense/` 文件夹内的依赖关系如下：`package/derived.kiwi` 依赖 `enum.kiwi`、`package/base-1.kiwi` 和 `package/base-2.kiwi`。`derived.kiwi` 使用了 `enum.kiwi`、`base-1.kiwi` 和 `base-2.kiwi` 中的类型。在解析时, 三个依赖文件的内容会被添加到 `derived.kiwi` 的前部。

```
enum.kiwi              \
package/base-1.kiwi ----> package/derived.kiwi
package/base-2.kiwi    /
```

## 构建优化

原始项目仅使用 `tsc` 编译代码，未采用打包工具。在使用 `vsce` 打包插件时会收到以下提示：

```bash
This extension consists of 590 files, out of which 341 are JavaScript files. For performance reasons, you should bundle your extension: https://aka.ms/vscode-bundle-extension
....
kiwi-vscode-1.0.3.vsix (590 files, 759.55KB)
```

本项目进行了构建优化：

1. 采用 `tsup` 作为构建工具
2. 使用 `pnpm workspace` 管理 `server/` 和 `client/` 两个模块

优化后的构建产物如下：

```bash
client build: CJS out/extension.js 1.02 KB
client build: CJS ⚡️ Build success in 27ms
client build: Done
server build: CJS out/server.js 19.45 KB
server build: CJS ⚡️ Build success in 111ms
...
kiwi-vscode-1.0.3.vsix (11 files, 131.39 KB)
```

压缩后的插件包体积减小了 80%，解压后的文件则更加精简。

## Logo 设计

Logo 由 [Slea.ai](https://slea.ai/) 生成，使用的提示词如下：

> a vector logo design, with the text "Kiwi", main symbol: messages, binary, code, programming language, the background is circular, Minimalistic, be used in Internet industry, clear background.

## 致谢

- [Cursor](https://www.cursor.com/)
- [Trae](https://www.trae.ai/)

## 协议

[MIT](./LICENSE.md)
