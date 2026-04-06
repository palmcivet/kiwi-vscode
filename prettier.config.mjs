/** @type {import("prettier").Config} */
export default {
  printWidth: 80,
  tabWidth: 2,
  semi: true,
  singleQuote: true,
  trailingComma: 'all',
  endOfLine: 'lf',
  arrowParens: 'always',
  bracketSameLine: true,
  plugins: ['@ianvs/prettier-plugin-sort-imports'],
  importOrder: ['^[./]'],
};
