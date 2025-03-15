## 项目背景
kiwi 消息格式是一种类似 Protobuf 的格式，本项目是 kiwi 的 VSCode 插件，支持以下功能

- 使用 TextMate 语法进行语法高亮
- 基本的语言配置（注释、括号等）
- 支持 Jump-to-definition, autocomplete, find-all-references, codelens 等语言插件的特性, 悬停时显示基本文档信息，以及有简单的代码检查
- 提供快速操作，包括更正错误的大小写和生成消息的下一个可用 ID（对于包含数百个字段的大型消息特别有用）

## 文件结构
- `client/`: LSP 服务的 VSCode 前端
- `server/`: LSP 服务的后端
- `syntaxes/`: TextMate 语法高亮
- `fixtures/`: 存放了测试数据
- `tree-sitter-kiwi/`: tree-sitter 语法
