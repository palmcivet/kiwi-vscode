#!/usr/bin/env node
/**
 * Cross-compile tree-sitter-kiwi prebuilds for all supported VSCode platforms
 * using zig as the C/C++ cross-compiler.
 *
 * This script bypasses node-gyp entirely because node-gyp's generated Makefiles
 * are tightly coupled to the host OS (e.g., macOS linker flags like -bundle,
 * -undefined dynamic_lookup, -arch). Instead, we invoke zig directly to compile
 * the C/C++ sources into a shared library (.node file).
 *
 * Usage:
 *   node scripts/build-prebuilds.mjs [target]
 *
 * Arguments:
 *   target - Optional. One of: all, darwin-arm64, darwin-x64, linux-x64, linux-arm64
 *            Defaults to "all".
 *
 * Prerequisites:
 *   - zig (https://ziglang.org/) must be installed and available in PATH
 *   - Node.js >= 18
 *   - pnpm dependencies installed (for node-addon-api headers)
 *   - prebuildify installed (we use its downloaded Node.js headers)
 */
import { execFileSync } from 'node:child_process';
import { existsSync, mkdirSync, readdirSync, rmSync } from 'node:fs';
import { homedir, tmpdir } from 'node:os';
import { basename, dirname, join, relative, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const root = resolve(__dirname, '..');

/**
 * @typedef {{
 *   platform: string,
 *   arch: string,
 *   zigTarget: string,
 *   sharedFlag: string,
 *   outputExt: string,
 * }} Target
 */

/** @type {Target[]} */
const TARGETS = [
  {
    platform: 'darwin',
    arch: 'arm64',
    zigTarget: 'aarch64-macos',
    sharedFlag: '-dynamiclib',
    outputExt: '.node',
  },
  {
    platform: 'darwin',
    arch: 'x64',
    zigTarget: 'x86_64-macos',
    sharedFlag: '-dynamiclib',
    outputExt: '.node',
  },
  {
    platform: 'linux',
    arch: 'x64',
    zigTarget: 'x86_64-linux-gnu',
    sharedFlag: '-shared',
    outputExt: '.node',
  },
  {
    platform: 'linux',
    arch: 'arm64',
    zigTarget: 'aarch64-linux-gnu',
    sharedFlag: '-shared',
    outputExt: '.node',
  },
];

/**
 * Verify that zig is installed and available.
 */
function checkZig() {
  try {
    const version = execFileSync('zig', ['version'], {
      encoding: 'utf-8',
    }).trim();
    console.log(`Using zig ${version}`);
  } catch {
    console.error(
      'Error: zig is not installed or not in PATH.\n' +
        'Install with: brew install zig (macOS) or see https://ziglang.org/download/',
    );
    process.exit(1);
  }
}

/**
 * Find the Node.js N-API headers directory.
 * N-API is ABI-stable across Node.js versions, so any version's headers work.
 *
 * Search order:
 *   1. prebuildify's cached headers (from previous builds)
 *   2. node-gyp's cached headers (~/.cache/node-gyp or ~/.node-gyp)
 *   3. System Node.js headers (e.g., from nvm)
 *   4. Download via node-gyp install
 *
 * @returns {string} path to the directory containing node_api.h etc.
 */
function findNodeHeaders() {
  const nodeVersion = process.versions.node;

  // 1. Check prebuildify's cached headers
  const tmpBase = join(tmpdir(), 'prebuildify', 'node');
  if (existsSync(tmpBase)) {
    const versions = readdirSync(tmpBase).sort();
    for (let i = versions.length - 1; i >= 0; i--) {
      const headersDir = join(tmpBase, versions[i], 'include', 'node');
      if (existsSync(join(headersDir, 'node_api.h'))) {
        return headersDir;
      }
    }
  }

  // 2. Check node-gyp's cache directories
  const home = homedir();
  /** @type {string[]} */
  const nodeGypPaths = [
    join(home, '.cache', 'node-gyp', nodeVersion, 'include', 'node'),
    join(home, '.node-gyp', nodeVersion, 'include', 'node'),
  ];
  for (const dir of nodeGypPaths) {
    if (existsSync(join(dir, 'node_api.h'))) {
      return dir;
    }
  }

  // 3. Check system Node.js headers (nvm, homebrew, etc.)
  const nodeInclude = join(dirname(process.execPath), '..', 'include', 'node');
  if (existsSync(join(nodeInclude, 'node_api.h'))) {
    return nodeInclude;
  }

  // 4. Download headers via node-gyp
  console.log('Downloading Node.js headers via node-gyp...');
  try {
    execFileSync('npx', ['node-gyp', 'install'], {
      cwd: root,
      stdio: 'inherit',
    });
    // Re-check node-gyp cache after download
    for (const dir of nodeGypPaths) {
      if (existsSync(join(dir, 'node_api.h'))) {
        return dir;
      }
    }
  } catch {
    // fall through
  }

  throw new Error(
    'Cannot find Node.js headers. Ensure node-gyp or Node.js dev headers are available.',
  );
}

/**
 * Find the node-addon-api include directory (provides napi.h C++ wrappers).
 *
 * @returns {string} path to the node-addon-api directory
 */
function findNodeAddonApiDir() {
  // Check NODE_ADDON_API_DIR env var first (useful in CI)
  if (process.env.NODE_ADDON_API_DIR) {
    const envDir = process.env.NODE_ADDON_API_DIR;
    if (existsSync(join(envDir, 'napi.h'))) {
      return envDir;
    }
  }
  try {
    const dir = execFileSync(
      'node',
      ['-e', "console.log(require('node-addon-api').include)"],
      { cwd: root, encoding: 'utf-8' },
    )
      .trim()
      .replace(/^"|"$/g, '');
    if (existsSync(join(dir, 'napi.h'))) {
      return dir;
    }
  } catch {
    // fall through
  }
  throw new Error(
    'Cannot find node-addon-api. Run pnpm install in tree-sitter-kiwi first.',
  );
}

/**
 * Build prebuild for a specific target platform by invoking zig directly.
 *
 * Compilation strategy:
 *   1. Compile src/parser.c (C11) → object
 *   2. Compile bindings/node/binding.cc (C++17 with N-API) → object
 *   3. Link into a shared library (.node)
 *
 * For N-API addons, symbols like napi_create_error are resolved at runtime
 * by the Node.js process. We use -undefined dynamic_lookup (macOS) or
 * --allow-shlib-undefined (Linux) to allow this.
 *
 * @param {Target} target
 * @param {string} nodeHeadersDir
 * @param {string} nodeAddonApiDir
 */
function buildTarget(target, nodeHeadersDir, nodeAddonApiDir) {
  const key = `${target.platform}-${target.arch}`;
  console.log(`\n${'='.repeat(60)}`);
  console.log(`Building ${key} (zig target: ${target.zigTarget})`);
  console.log('='.repeat(60));

  const outputDir = join(root, 'prebuilds', `${key}`);
  mkdirSync(outputDir, { recursive: true });

  const tmpDir = join(root, '.tmp-build');
  mkdirSync(tmpDir, { recursive: true });

  const outputFile = join(outputDir, `tree-sitter-kiwi${target.outputExt}`);

  // Common include directories
  const includes = [
    `-I${join(root, 'src')}`,
    `-I${nodeHeadersDir}`,
    `-I${nodeAddonApiDir}`,
  ];

  // Common defines
  const defines = [
    '-DNODE_GYP_MODULE_NAME=tree_sitter_kiwi_binding',
    '-DBUILDING_NODE_EXTENSION',
    '-DNAPI_CPP_EXCEPTIONS',
  ];

  const commonFlags = ['-target', target.zigTarget, '-O2', '-fPIC'];

  // Step 1: Compile C sources (parser.c, optional scanner.c)

  /** @type {string[]} */
  const cSources = [join(root, 'src', 'parser.c')];
  const scannerPath = join(root, 'src', 'scanner.c');
  if (existsSync(scannerPath)) {
    cSources.push(scannerPath);
  }

  /** @type {string[]} */
  const objectFiles = [];

  for (const src of cSources) {
    const baseName = basename(src, '.c') + '.o';
    const objFile = join(tmpDir, `${key}-${baseName}`);
    objectFiles.push(objFile);

    console.log(`  CC  ${relative(root, src)}`);
    execFileSync(
      'zig',
      [
        'cc',
        ...commonFlags,
        '-c',
        '-std=c11',
        ...includes,
        ...defines,
        '-o',
        objFile,
        src,
      ],
      { cwd: root, stdio: 'inherit' },
    );
  }

  // Step 2: Compile C++ sources (binding.cc)

  const bindingSrc = join(root, 'bindings', 'node', 'binding.cc');
  const bindingObj = join(tmpDir, `${key}-binding.o`);
  objectFiles.push(bindingObj);

  console.log(`  CXX ${relative(root, bindingSrc)}`);
  execFileSync(
    'zig',
    [
      'c++',
      ...commonFlags,
      '-c',
      '-std=c++17',
      '-fexceptions',
      ...includes,
      ...defines,
      '-o',
      bindingObj,
      bindingSrc,
    ],
    { cwd: root, stdio: 'inherit' },
  );

  // Step 3: Link into shared library (.node)

  /** @type {string[]} */
  const linkArgs = [
    'c++',
    ...commonFlags,
    target.sharedFlag,
    '-o',
    outputFile,
    ...objectFiles,
  ];

  // Platform-specific linker flags for allowing undefined N-API symbols
  // (they are provided by the Node.js runtime at load time)
  if (target.platform === 'darwin') {
    linkArgs.push('-Wl,-undefined,dynamic_lookup');
  } else if (target.platform === 'linux') {
    linkArgs.push('-Wl,--allow-shlib-undefined');
  }

  console.log(`  LINK ${relative(root, outputFile)}`);
  execFileSync('zig', linkArgs, {
    cwd: root,
    stdio: 'inherit',
  });

  // Clean up object files
  for (const obj of objectFiles) {
    rmSync(obj, { force: true });
  }

  if (existsSync(outputFile)) {
    console.log(`  Successfully built ${key}`);
  } else {
    throw new Error(`Output file not found: ${outputFile}`);
  }
}

// prebuildify compatibility
// node-gyp-build expects a specific file naming convention in prebuilds/.
// The standard is: prebuilds/{platform}-{arch}/{name}.node
// Our output already matches this pattern, so node-gyp-build will find it.

const requestedTarget = process.argv[2] || 'all';

checkZig();

const nodeHeadersDir = findNodeHeaders();
const nodeAddonApiDir = findNodeAddonApiDir();

console.log(`Node.js headers: ${nodeHeadersDir}`);
console.log(`node-addon-api: ${nodeAddonApiDir}`);

/**
 * Resolve the list of targets to build from the CLI argument.
 * Supports: "all", a single target like "linux-x64", or comma-separated
 * targets like "linux-x64,linux-arm64".
 *
 * @param {string} requested
 * @returns {Target[]}
 */
function resolveTargets(requested) {
  if (requested === 'all') {
    return TARGETS;
  }
  const names = requested
    .split(',')
    .map((s) => s.trim())
    .filter(Boolean);
  /** @type {Target[]} */
  const resolved = [];
  for (const name of names) {
    const target = TARGETS.find((t) => `${t.platform}-${t.arch}` === name);
    if (!target) {
      console.error(
        `Unknown target: ${name}\n` +
          `Available targets: ${TARGETS.map((t) => `${t.platform}-${t.arch}`).join(', ')}, all`,
      );
      process.exit(1);
    }
    resolved.push(target);
  }
  return resolved;
}

const selectedTargets = resolveTargets(requestedTarget);

if (requestedTarget === 'all') {
  // Clean entire prebuilds directory when building all targets
  const prebuildsDir = join(root, 'prebuilds');
  if (existsSync(prebuildsDir)) {
    rmSync(prebuildsDir, { recursive: true });
    console.log('Cleaned previous prebuilds');
  }
} else {
  // Clean only the selected target directories
  for (const target of selectedTargets) {
    const targetDir = join(
      root,
      'prebuilds',
      `${target.platform}-${target.arch}`,
    );
    if (existsSync(targetDir)) {
      rmSync(targetDir, { recursive: true });
      console.log(
        `Cleaned previous prebuild for ${target.platform}-${target.arch}`,
      );
    }
  }
}

let succeeded = 0;
let failed = 0;
/** @type {string[]} */
const failures = [];

for (const target of selectedTargets) {
  try {
    buildTarget(target, nodeHeadersDir, nodeAddonApiDir);
    succeeded++;
  } catch (error) {
    const key = `${target.platform}-${target.arch}`;
    console.error(`\nFailed to build ${key}:`, error.message);
    failures.push(key);
    failed++;
  }
}

console.log(`\n${'='.repeat(60)}`);
console.log(`Build complete: ${succeeded} succeeded, ${failed} failed`);
if (failures.length > 0) {
  console.log(`Failed targets: ${failures.join(', ')}`);
}

// Clean up temp build directory
rmSync(join(root, '.tmp-build'), { recursive: true, force: true });

if (failures.length > 0) {
  process.exit(1);
}
