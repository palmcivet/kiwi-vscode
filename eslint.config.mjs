import antfu from '@antfu/eslint-config';

export default antfu({
  ignores: [
    'node_modules/**',
    'client/node_modules/**',
    'client/out/**',
    'server/node_modules/**',
    'server/out/**',
    'tree-sitter-kiwi/bindings',
    'tree-sitter-kiwi/*.toml',
  ],
  stylistic: {
    semi: true,
  },
});
