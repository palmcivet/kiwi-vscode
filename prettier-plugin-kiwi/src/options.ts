import type { ParserOptions, SupportOption } from 'prettier';

interface PrintOptions extends ParserOptions<string> {
  trimTrailingWhitespace: boolean;
  alignComments: boolean;
  alignFields: boolean;
}

export type PrettierOptions = ParserOptions & PrintOptions;

export const options: Record<keyof PrintOptions, SupportOption> = {
  trimTrailingWhitespace: {
    name: 'trimTrailingWhitespace',
    category: 'kiwi',
    type: 'boolean',
    default: true,
    description: 'Trim trailing whitespace in the end of lines.',
  },
  /**
   * Set to `true` to align comments in the same column.
   *
   * ```kiwi
   * int d = 1;   // This is a comment
   * int64 b = 2; // This is another comment
   * int a = 3;   // This is the last comment
   * ```
   */
  alignComments: {
    name: 'alignComments',
    category: 'kiwi',
    type: 'boolean',
    default: true,
    description:
      'Align consecutive comments after entries and items vertically. This applies to comments that are after entries or array items.',
  },
  /**
   * Set to `true` to align fields in the same column.
   *
   * ```kiwi
   * message Foo {
   *   int   d = 1; // This is a comment
   *   int64 b = 2; // This is another comment
   *   int   a = 3; // This is the last comment
   * }
   * ```
   */
  alignFields: {
    name: 'alignFields',
    category: 'kiwi',
    type: 'boolean',
    default: true,
    description:
      'Align consecutive fields after entries and items vertically. This applies to fields that are after entries or array items.',
  },
};
