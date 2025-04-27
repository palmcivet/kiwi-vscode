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
- `prettier-plugin-kiwi/`: prettier 插件

## 基本准则
- 所有代码和文档都使用英文
- 始终声明每个变量和函数的类型（包括参数和返回值）
- 必要时，创建类型，抽离函数和文件
- 使用 JSDoc 为公共类和方法编写文档
- 使用完整单词，避免缩写和拼写错误。标准缩写（如 API、URL 等）除外
- 给出完整的代码，禁止使用伪代码
- 关键路径上输出必要的日志

## 注释风格
- 注释统一使用英文
- 函数
  ```ts
  /**
   * ...
   *
   * @param ...
   * @returns ...
   */
  ```
  function foo(): void {}
- 代码注释
  ```ts
  // comment
  const a = 0;
  ```
- 接口字段
  ```ts
  interface IncludeDirective {
    /** The raw path string extracted from the include directive */
    path: string;
  }
  ```

## 测试要求
每个函数的测试用例需要包含正常情况和边界情况

## 通用脚本

- `clean`：清理构建产物
- `build`：编译。统一
- `test`：测试。统一
- `dev`：开发。各模块单独执行
