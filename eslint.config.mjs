import antfu from '@antfu/eslint-config';

export default antfu({
  ignores: [
    'node_modules/**',
    'client/node_modules/**',
    'client/out/**',
    'server/node_modules/**',
    'server/out/**',
    '**/*.toml',
  ],
  stylistic: {
    semi: true,
  },
});
