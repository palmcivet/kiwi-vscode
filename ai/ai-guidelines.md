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
