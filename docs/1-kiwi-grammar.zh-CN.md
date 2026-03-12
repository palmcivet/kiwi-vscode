# Kiwi 格式化规范

本文档定义 Kiwi 语言源文件的标准格式。格式化器的目标是将任意合法 Kiwi 源码转换为符合本规范的统一风格。

- [Kiwi 格式化规范](#kiwi-格式化规范)
  - [1 文件结构](#1-文件结构)
  - [2 缩进](#2-缩进)
  - [3 空格规则](#3-空格规则)
    - [3.1 赋值符号](#31-赋值符号)
    - [3.2 分号](#32-分号)
    - [3.3 deprecated 标记](#33-deprecated-标记)
    - [3.4 类型与字段名](#34-类型与字段名)
    - [3.5 数组标记](#35-数组标记)
    - [3.6 声明关键字](#36-声明关键字)
    - [3.7 开花括号](#37-开花括号)
  - [4 空行规则](#4-空行规则)
    - [4.1 顶层空行](#41-顶层空行)
    - [4.2 声明体内空行](#42-声明体内空行)
  - [5 注释](#5-注释)
    - [5.1 注释空格规范](#51-注释空格规范)
    - [5.2 多斜杠注释](#52-多斜杠注释)
    - [5.3 内联注释](#53-内联注释)
    - [5.4 花括号后的注释](#54-花括号后的注释)
    - [5.5 独立注释](#55-独立注释)
    - [5.6 续行注释](#56-续行注释)
  - [6 package 声明](#6-package-声明)
  - [7 include 指令](#7-include-指令)
    - [7.1 无效的 include 语法](#71-无效的-include-语法)
  - [8 enum 声明](#8-enum-声明)
    - [8.1 字段格式](#81-字段格式)
    - [8.2 空 enum](#82-空-enum)
  - [9 message 声明](#9-message-声明)
    - [9.1 字段格式](#91-字段格式)
    - [9.2 空 message](#92-空-message)
  - [10 struct 声明](#10-struct-声明)
    - [10.1 字段格式](#101-字段格式)
    - [10.2 空 struct](#102-空-struct)
  - [11 类型系统](#11-类型系统)
    - [11.1 原始类型](#111-原始类型)
    - [11.2 自定义类型](#112-自定义类型)
    - [11.3 数组类型](#113-数组类型)
  - [12 综合示例](#12-综合示例)

## 1 文件结构

一个 Kiwi 文件由以下部分按顺序组成，每个部分均可省略：

```kiwi
[package 声明]
[include 指令]
[类型声明 (enum / message / struct)]
```

文件以恰好一个换行符结尾。空文件不输出任何内容。

## 2 缩进

- 使用空格缩进，默认缩进宽度为 2 个空格。
- 声明体（`{` 与 `}` 之间）的内容缩进一级。
- 顶层元素不缩进。

## 3 空格规则

### 3.1 赋值符号

`=` 前后各恰好一个空格：

```kiwi
int id = 1;
ACTIVE = 0;
```

### 3.2 分号

`;` 前无空格，紧跟在值或 `[deprecated]` 之后：

```kiwi
int id = 1;
int old = 2 [deprecated];
float x;
```

### 3.3 deprecated 标记

`[deprecated]` 前恰好一个空格，与值之间分隔：

```kiwi
int oldField = 1 [deprecated];
```

### 3.4 类型与字段名

类型名与字段名之间恰好一个空格：

```kiwi
int id = 1;
string[] names = 2;
User author = 3;
```

### 3.5 数组标记

`[]` 紧跟类型名，中间无空格：

```kiwi
int[] numbers = 1;
string[] names = 2;
User[] users = 3;
```

### 3.6 声明关键字

关键字（`package`、`enum`、`message`、`struct`）与名称之间恰好一个空格：

```kiwi
package Example;
enum Status { ... }
message User { ... }
struct Point { ... }
```

### 3.7 开花括号

`{` 与声明名称之间恰好一个空格，且 `{` 始终在声明同一行（K&R 风格）：

```kiwi
message User {
  ...
}
```

## 4 空行规则

### 4.1 顶层空行

顶层元素（package 声明、include 指令、类型声明、独立注释）之间的空行规则：

- **保留**源码中已有的空行（多个连续空行折叠为一个）。
- 若源码中两个顶层元素之间没有空行，则格式化后也不插入空行。

三个空行折叠为一个；`Foo` 与 `Bar` 之间原有的一个空行保留。

### 4.2 声明体内空行

声明体（`enum_body`、`message_body`、`struct_body`）内部：

- 字段之间的空行一律**移除**。
- 独立注释之前的空行**保留**（多个折叠为一个）。
- 独立注释之后、下一个字段之前的空行移除。

```kiwi
// 输入                        // 输出
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

`id` 与 `title` 之间的空行被移除（两个字段之间）。`// Section` 注释前的空行被保留。

## 5 注释

Kiwi 仅支持 `//` 单行注释。

### 5.1 注释空格规范

`//` 后恰好一个空格，多余空格被压缩：

| 输入 | 输出 |
|------|------|
| `//comment` | `// comment` |
| `//  extra spaces` | `// extra spaces` |
| `//` (空注释) | `//` |

### 5.2 多斜杠注释

`//` 之后的额外斜杠被视为注释内容的一部分。规范化规则：在前两个 `//` 之后插入一个空格，余下内容原样保留：

| 输入 | 输出 | 解释 |
|------|------|------|
| `///comment` | `// /comment` | `//` + 空格 + `/comment` |
| `/// comment` | `// / comment` | `//` + 空格 + `/ comment` |
| `////comment` | `// //comment` | `//` + 空格 + `//comment` |

注意：`/// @include` 是 include 指令的语法前缀，不属于普通注释，不适用此规则。

### 5.3 内联注释

出现在字段、声明、或指令同一行末尾的注释称为内联注释。格式化后，内联注释与前方内容之间恰好一个空格：

```kiwi
int id = 1; // user id
package Example; // package name
/// @include "types.kiwi" // note
```

内联注释的判定条件：
- 注释与前方元素在源码中位于同一行。
- 前方元素不是另一个注释。
- 前方元素不是开花括号 `{`。

### 5.4 花括号后的注释

紧跟在 `{` 之后同一行出现的注释不视为内联注释，而是作为声明体的第一个独立注释：

```kiwi
// 输入                        // 输出
message Logger {//Comment      message Logger {
  int level = 1;                 // Comment
}                                int level = 1;
                               }
```

### 5.5 独立注释

不与前方元素在同一行的注释为独立注释，单独占一行，遵循所在上下文的缩进：

```kiwi
message User {
  // Field group
  int id = 1;
  // Another group
  string name = 2;
}
```

### 5.6 续行注释

字段的内联注释之后、下一行出现的独立注释是独立的，不会合并到内联注释中：

```kiwi
int param = 4; // first line
// second line
int other = 5;
```

## 6 package 声明

格式：`package Name;`

- 关键字 `package` 后一个空格。
- 名称后紧跟 `;`，无空格。
- 多余空格被移除。

```kiwi
// 输入                        // 输出
package    Example   ;         package Example;
```

## 7 include 指令

格式：`/// @include "path"`

- 路径统一使用双引号包裹。
- 单引号或无引号的路径自动转换为双引号。

| 输入 | 输出 |
|------|------|
| `/// @include basic.kiwi` | `/// @include "basic.kiwi"` |
| `/// @include 'types.kiwi'` | `/// @include "types.kiwi"` |
| `/// @include "base.kiwi"` | `/// @include "base.kiwi"` |

### 7.1 无效的 include 语法

include 指令的语法前缀是 `/// @include `（末尾有一个空格）。不符合此精确模式的内容会被解析为普通注释，按注释规则格式化：

| 输入 | 解析为 | 输出 |
|------|--------|------|
| `///@include 'common.kiwi'` | 注释 | `// /@include 'common.kiwi'` |
| `/// @include"types.kiwi"` | 注释 | `// / @include"types.kiwi"` |

## 8 enum 声明

```kiwi
enum Name {
  FIELD_A = 0;
  FIELD_B = 1;
}
```

### 8.1 字段格式

```kiwi
NAME = VALUE;
```

- 名称、`=`、值之间各一个空格。
- `;` 紧跟值，前无空格。

### 8.2 空 enum

无字段且无注释的 enum 体格式化为单行：

```kiwi
enum Empty {}
```

## 9 message 声明

```kiwi
message Name {
  type fieldName = number;
  type fieldName = number [deprecated];
}
```

### 9.1 字段格式

```kiwi
type name = number;
type name = number [deprecated];
```

- 类型、名称、`=`、编号之间各一个空格。
- `[deprecated]` 可选，出现时前面一个空格。
- `;` 紧跟最后一个元素，前无空格。

### 9.2 空 message

```kiwi
message Empty {}
```

## 10 struct 声明

```kiwi
struct Name {
  type fieldName;
}
```

### 10.1 字段格式

```kiwi
type name;
```

- 类型与名称之间一个空格。
- `;` 紧跟名称，前无空格。
- struct 字段没有编号和 deprecated 标记。

### 10.2 空 struct

```kiwi
struct Empty {}
```

## 11 类型系统

### 11.1 原始类型

Kiwi 支持以下原始类型：

`bool`、`byte`、`int32`、`int64`、`uint32`、`uint64`、`float`、`double`、`string`

注意：`int`、`uint` 等简写形式在语法中会被匹配为 `identifier`，与自定义类型的处理方式相同。

### 11.2 自定义类型

可以引用其他已声明的 enum、message 或 struct 名称作为字段类型：

```kiwi
message User {
  Role role = 1;
  Settings settings = 2;
}
```

### 11.3 数组类型

在类型名后加 `[]` 表示数组。`[]` 紧贴类型名，中间无空格。原始类型和自定义类型均可使用数组：

```kiwi
int[] numbers = 1;
string[] names = 2;
User[] users = 3;
```

Kiwi 不支持多维数组。

## 12 综合示例

格式化前：

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

格式化后：

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
