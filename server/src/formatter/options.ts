/**
 * Formatter options, similar to editorconfig.
 * see [spec](https://spec.editorconfig.org/#id12)
 */
export interface FormatterOptions {
  /**
   * Set to `tab` or `space` to use tabs or spaces for indentation, respectively.
   * Option `tab` implies that an indentation is to be filled by as many hard tabs
   * as possible, with the rest of the indentation filled by spaces.
   * A non-normative explanation can be found in the [indentation](https://spec.editorconfig.org/#id16) section.
   *
   * The values are case insensitive.
   */
  indentStyle: 'space' | 'tab';
  /**
   * Set to a whole number defining the number of columns used for each indentation level
   * and the width of soft tabs (when supported).
   * If this equals `tab`, the `indentSize` shall be set to the tab size,
   * which should be `tabWidth` (if specified); else, the tab size set by the editor.
   *
   * The values are case insensitive.
   */
  indentSize: number;
  /**
   * Set to a whole number defining the number of columns used to represent a tab character.
   * This defaults to the value of `indentSize` and should not usually need to be specified.
   */
  tabWidth: number;
  /**
   * Set to `lf`, `cr`, or `crlf` to control how line breaks are represented.
   *
   * The values are case insensitive.
   */
  endOfLine: 'lf' | 'cr' | 'crlf';
  /**
   * Set to `true` to remove all whitespace characters preceding newline characters
   * in the file and `false` to ensure it doesn’t.
   */
  trimTrailingWhitespace: boolean;
  /**
   * Set to `true` ensure file ends with a newline when saving and `false` to ensure it doesn’t.
   * Editors must not insert newlines in empty files when saving those files,
   * even if `insert_final_newline = true`.
   */
  insertFinalNewline: boolean;
}

export const DEFAULT_OPTIONS: FormatterOptions = {
  indentStyle: 'space',
  indentSize: 2,
  tabWidth: 2,
  endOfLine: 'lf',
  trimTrailingWhitespace: true,
  insertFinalNewline: true,
};
