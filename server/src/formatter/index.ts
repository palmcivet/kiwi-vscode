import { createRequire } from 'node:module';
import { join } from 'node:path';
import type { Plugin } from 'prettier';
import { configStore } from '@server/store';

interface PrettierInstance {
  /**
   * @description The resolved prettier module
   */
  prettier: typeof import('prettier');
  /**
   * @description The resolved prettier-plugin-kiwi module
   */
  plugin: Plugin;
  /**
   * @description Whether the instance was resolved from the workspace's local node_modules
   */
  isLocal: boolean;
}

let cachedInstance: PrettierInstance | null = null;
let cachedWorkspaceRoot: string | null | undefined;

/**
 * @description Resolves prettier and prettier-plugin-kiwi, prioritizing the workspace's
 * local node_modules. Falls back to the bundled versions shipped with the extension.
 *
 * Both prettier and prettier-plugin-kiwi must be resolvable from the workspace
 * for the local version to be used; otherwise, the bundled fallback is used
 * to avoid version incompatibilities.
 *
 * @returns The resolved prettier instance with plugin
 */
function resolvePrettier(): PrettierInstance {
  const workspaceRoot = configStore.getWorkspaceRoot();

  if (cachedInstance && cachedWorkspaceRoot === workspaceRoot) {
    return cachedInstance;
  }

  if (workspaceRoot) {
    try {
      const localRequire = createRequire(join(workspaceRoot, 'package.json'));
      const localPrettier = localRequire(
        'prettier',
      ) as typeof import('prettier');
      const localPlugin = localRequire('prettier-plugin-kiwi') as Plugin;

      cachedInstance = {
        prettier: localPrettier,
        plugin: localPlugin,
        isLocal: true,
      };
      cachedWorkspaceRoot = workspaceRoot;
      console.log(
        `[kiwi-formatter] Using local prettier from: ${workspaceRoot}`,
      );
      return cachedInstance;
    } catch {
      // Local resolution failed, fall back to bundled version
    }
  }

  // Fallback: use the bundled prettier shipped with the extension
  const bundledPrettier = require('prettier') as typeof import('prettier');
  const bundledPlugin = require('prettier-plugin-kiwi') as Plugin;

  cachedInstance = {
    prettier: bundledPrettier,
    plugin: bundledPlugin,
    isLocal: false,
  };
  cachedWorkspaceRoot = workspaceRoot;
  console.log('[kiwi-formatter] Using bundled prettier');
  return cachedInstance;
}

/**
 * @description Formats Kiwi source code using prettier with prettier-plugin-kiwi.
 *
 * Prioritizes the workspace's local prettier installation over the bundled one.
 * When using the local prettier, the user's prettier configuration files
 * (.prettierrc, prettier.config.js, etc.) are also respected.
 *
 * @param text - The Kiwi source code to format
 * @returns The formatted source code
 */
export async function format(text: string): Promise<string> {
  const { prettier, plugin, isLocal } = resolvePrettier();

  let userConfig: Record<string, unknown> = {};
  if (isLocal) {
    const workspaceRoot = configStore.getWorkspaceRoot();
    if (workspaceRoot) {
      const resolved = await prettier.resolveConfig(workspaceRoot);
      if (resolved) {
        userConfig = resolved;
      }
    }
  }

  return await prettier.format(text, {
    ...userConfig,
    parser: 'kiwi',
    plugins: [plugin],
    tabWidth: (userConfig.tabWidth as number | undefined) ?? 2,
    useTabs: (userConfig.useTabs as boolean | undefined) ?? false,
  });
}
