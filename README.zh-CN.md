# Kiwi VSCode

[English](./README.md) | 中文

> Better support for the Kiwi message format in Visual Studio Code.

本项目是从 [connorskees/kiwi-lsp](https://github.com/connorskees/kiwi-lsp) 分叉而来，后者已发布在 [VSCode 市场](https://marketplace.visualstudio.com/items?itemName=connorskees.kiwi-lsp)，标识为 `connorskees.kiwi-lsp`。

## 基础功能

原始插件提供了以下功能：

- 使用 TextMate 进行语法高亮
- 基础语言配置（如注释、括号等）
- 转到定义、转到引用、自动补全、查找所有引用、Code Lens、悬停显示文档以及简单的代码检查
- 快速修复：用于纠正错误的大小写和为消息生成下一个可用的 id（对于包含数百个字段的大型消息尤其有用）

## `@include` 语法
### 背景

原始插件代码分析仅针对打开的文件，跨文件引用（比如 `derived.kiwi` 用了 `enum.kiwi`、`base-1.kiwi`、`base-2.kiwi` 的类型）时，现有的功能不支持这种用法，代码检查会出错。

为此设计了一种语法，在文件的开头，使用 `/// @include filename.kiwi` 来引入其他 kiwi 文件。示例如下：

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
    message Vec {}

    /// @include './base-1.kiwi'  // 无效，因为前面有
    message Vector {}
    ```
- 必须以 `/// @include ` 开头
- 文件支持绝对路径和相对路径
- 文件名可使用 `''` 或 `""` 包裹，也可以不写引号
- 文件名大小写敏感
- 多次引用时只会导入一次，类似 `#pragma once`

### 插件适配

为适配该语法，VSCode 插件实现了以下功能：

1. 点击 `@include` 的文件时能够跳转到对应文件
2. 在解释打开的文件时，会把有效的 `@include` 指令所引用的文件内容拼接到当前文件，因此等效在当前文件声明了所有依赖的内容
3. 拼接文件内容只发生在解析时，警告和错误仍对应当前文件
4. Code Action 也能给出正确的建议
5. 转到定义：点击类型时能够跳转到原文件中对应的代码
6. 自动补全：在支持 `@include` 指令之后，引用文件中的类型也会加入到候选列表

### 测试数据

见 `fixture/intellisense/` 目录，该文件夹是语言服务的测试数据。

`intellisense/` 文件夹内的依赖关系如下：`package/derived.kiwi` 依赖 `enum.kiwi`、`package/base-1.kiwi` 和 `package/base-2.kiwi`。`derived.kiwi` 使用了 `enum.kiwi`、`base-1.kiwi` 和 `base-2.kiwi` 中的类型。在解析时, 三个依赖文件的内容会被添加到 `derived.kiwi` 的前部。

```
enum.kiwi              \
package/base-1.kiwi ----> package/derived.kiwi
package/base-2.kiwi    /
```

## 构建方式

原始项目使用 `tsc` 编译代码，没有使用 bundler，在打包插件时 `vsce` 会提示以下信息：

```bash
This extension consists of 590 files, out of which 341 are JavaScript files. For performance reasons, you should bundle your extension: https://aka.ms/vscode-bundle-extension
....
kiwi-vscode-1.0.3.vsix (590 files, 759.55KB)
```

优化后采用 tsup 构建，并且使用 *pnpm workspace* 来管理 `server/` 和 `client/` 两个模块，原始构建产物如下：

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

## 致谢

- [Cursor](https://www.cursor.com/)
- [Trae](https://www.trae.ai/)

## 协议

MIT
