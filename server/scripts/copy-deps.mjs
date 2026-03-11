/**
 * Copies only the external runtime dependencies (prettier, tree-sitter, etc.)
 * into server/out/node_modules/ for the VSCode extension package.
 */

import { cpSync, mkdirSync, rmSync } from 'node:fs';
import { createRequire } from 'node:module';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const rootDir = resolve(__dirname, '..');
const serverOutDir = join(rootDir, 'out');
const nodeModulesDir = join(serverOutDir, 'node_modules');

// Clean up previous node_modules in server/out
rmSync(nodeModulesDir, { recursive: true, force: true });
mkdirSync(nodeModulesDir, { recursive: true });

// Use require.resolve to locate packages through pnpm's symlink structure
const require = createRequire(join(rootDir, 'package.json'));

// 1. Copy prettier (npm package, resolve through pnpm symlinks)
const prettierPkgPath = require.resolve('prettier/package.json');
const prettierDir = dirname(prettierPkgPath);
const prettierDest = join(nodeModulesDir, 'prettier');

cpSync(prettierDir, prettierDest, { recursive: true });
console.info(`Copied prettier from ${prettierDir}`);

// 2. Copy prettier-plugin-kiwi (workspace package, only out/ + package.json)
const pluginPkgPath = require.resolve('prettier-plugin-kiwi/package.json');
const pluginDir = dirname(pluginPkgPath);
const pluginDest = join(nodeModulesDir, 'prettier-plugin-kiwi');

mkdirSync(pluginDest, { recursive: true });
cpSync(join(pluginDir, 'package.json'), join(pluginDest, 'package.json'));
cpSync(join(pluginDir, 'out'), join(pluginDest, 'out'), { recursive: true });
console.info(`Copied prettier-plugin-kiwi from ${pluginDir}`);

// 3. Copy tree-sitter (native module with prebuilds, resolved from plugin's deps)
const pluginRequire = createRequire(join(pluginDir, 'package.json'));

const treeSitterPkgPath = pluginRequire.resolve('tree-sitter/package.json');
const treeSitterDir = dirname(treeSitterPkgPath);
const treeSitterDest = join(nodeModulesDir, 'tree-sitter');

const treeSitterDeps = [
  { path: 'package.json', recursive: false },
  { path: 'index.js', recursive: false },
  { path: 'prebuilds', recursive: true },
];
mkdirSync(treeSitterDest, { recursive: true });
for (const { path, recursive } of treeSitterDeps) {
  cpSync(join(treeSitterDir, path), join(treeSitterDest, path), { recursive });
}
console.info(`Copied tree-sitter from ${treeSitterDir}`);

// 4. Copy tree-sitter-kiwi (workspace native module with prebuilds)
const treeSitterKiwiPkgPath = pluginRequire.resolve(
  'tree-sitter-kiwi/package.json',
);
const treeSitterKiwiDir = dirname(treeSitterKiwiPkgPath);
const treeSitterKiwiDest = join(nodeModulesDir, 'tree-sitter-kiwi');

mkdirSync(join(treeSitterKiwiDest, 'src'), { recursive: true });
const treeSitterKiwiDeps = [
  { path: 'package.json', recursive: false },
  { path: 'bindings', recursive: true },
  { path: 'prebuilds', recursive: true },
  { path: 'src/node-types.json', recursive: true },
];
for (const { path, recursive } of treeSitterKiwiDeps) {
  cpSync(join(treeSitterKiwiDir, path), join(treeSitterKiwiDest, path), {
    recursive,
  });
}
console.info(`Copied tree-sitter-kiwi from ${treeSitterKiwiDir}`);

// 5. Copy node-gyp-build (runtime dependency of tree-sitter and tree-sitter-kiwi)
const treeSitterRequire = createRequire(join(treeSitterDir, 'package.json'));
const nodeGypBuildPkgPath = treeSitterRequire.resolve(
  'node-gyp-build/package.json',
);
const nodeGypBuildDir = dirname(nodeGypBuildPkgPath);
const nodeGypBuildDest = join(nodeModulesDir, 'node-gyp-build');

cpSync(nodeGypBuildDir, nodeGypBuildDest, { recursive: true });
console.info(`Copied node-gyp-build from ${nodeGypBuildDir}`);

// Summary
console.info(`\nDependencies copied to ${nodeModulesDir}`);
