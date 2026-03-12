import type { ExtensionContext } from 'vscode';
import { gt, valid } from 'semver';
import { commands, env, Uri, window, workspace } from 'vscode';
import { PluginKey, PluginVersion } from '@client/constant';

/**
 * @description GitHub API constants
 */
const GITHUB_API_URL =
  'https://api.github.com/repos/palmcivet/kiwi-vscode/releases/latest';

/**
 * @description Check interval in milliseconds (24 hours)
 */
const CHECK_INTERVAL_MS = 24 * 60 * 60 * 1000;

/**
 * @description Request timeout in milliseconds
 */
const REQUEST_TIMEOUT_MS = 10_000;

/**
 * @description Startup delay before first check in milliseconds
 */
const STARTUP_DELAY_MS = 5_000;

/**
 * @description globalState keys
 */
const STATE_LAST_CHECK_TIME = 'updateChecker.lastCheckTime';
const STATE_LATEST_VERSION = 'updateChecker.latestVersion';
const STATE_DISMISSED_VERSION = 'updateChecker.dismissedVersion';

/**
 * @description GitHub API response shape (only the fields we need)
 */
interface GitHubRelease {
  tag_name: string;
  html_url: string;
}

/**
 * @description Fetch the latest release info from GitHub API.
 *
 * Uses the global `fetch` API (available in Electron 19+ / VSCode 1.75+).
 * Returns null on any error (network, timeout, rate limiting, parse errors).
 */
async function fetchLatestRelease(): Promise<GitHubRelease | null> {
  try {
    const controller = new AbortController();
    const timeoutId = setTimeout(() => controller.abort(), REQUEST_TIMEOUT_MS);

    const response = await fetch(GITHUB_API_URL, {
      headers: {
        Accept: 'application/vnd.github.v3+json',
        'User-Agent': `kiwi-vscode/${PluginVersion}`,
      },
      signal: controller.signal,
    });

    clearTimeout(timeoutId);

    if (!response.ok) {
      return null;
    }

    const data = (await response.json()) as GitHubRelease;
    return data;
  } catch {
    // Network errors, timeouts, AbortError, JSON parse errors -- all silent
    return null;
  }
}

/**
 * Normalize a GitHub tag name to a semver version string.
 * Strips leading 'v' prefix if present (e.g., "v1.0.5" -> "1.0.5").
 */
function normalizeVersion(tagName: string): string | null {
  const cleaned = tagName.startsWith('v') ? tagName.slice(1) : tagName;
  return valid(cleaned);
}

/**
 * Show an update notification to the user with action buttons.
 */
async function showUpdateNotification(
  context: ExtensionContext,
  latestVersion: string,
  releaseUrl: string,
): Promise<void> {
  const message = `Kiwi VSCode v${latestVersion} is available (current: v${PluginVersion}).`;
  const viewRelease = 'View Release';
  const dismiss = 'Dismiss';

  const selection = await window.showInformationMessage(
    message,
    viewRelease,
    dismiss,
  );

  if (selection === viewRelease) {
    await env.openExternal(Uri.parse(releaseUrl));
  } else if (selection === dismiss) {
    await context.globalState.update(STATE_DISMISSED_VERSION, latestVersion);
  }
}

/**
 * Perform the update check: fetch latest release, compare versions,
 * and notify the user if an update is available.
 *
 * @param context - The extension context
 * @param manual - Whether this was triggered manually (bypasses cache and dismissed version)
 */
async function performUpdateCheck(
  context: ExtensionContext,
  manual: boolean,
): Promise<void> {
  // Check if the feature is enabled (skip check for manual invocations)
  if (!manual) {
    const config = workspace.getConfiguration(PluginKey);
    const enabled = config.get<boolean>('checkForUpdates', true);
    if (!enabled) {
      return;
    }

    // Check cache: skip if last check was within the interval
    const lastCheckTime = context.globalState.get<number>(
      STATE_LAST_CHECK_TIME,
      0,
    );
    if (Date.now() - lastCheckTime < CHECK_INTERVAL_MS) {
      return;
    }
  }

  const release = await fetchLatestRelease();
  if (!release) {
    if (manual) {
      window.showInformationMessage(
        'Kiwi VSCode: Unable to check for updates. Please try again later.',
      );
    }
    return;
  }

  // Update last check time
  await context.globalState.update(STATE_LAST_CHECK_TIME, Date.now());

  const latestVersion = normalizeVersion(release.tag_name);
  if (!latestVersion) {
    return;
  }

  // Store latest known version
  await context.globalState.update(STATE_LATEST_VERSION, latestVersion);

  // Compare versions
  if (!gt(latestVersion, PluginVersion)) {
    if (manual) {
      window.showInformationMessage('Kiwi VSCode is up to date.');
    }
    return;
  }

  // Check if user dismissed this version (skip for manual checks)
  if (!manual) {
    const dismissedVersion = context.globalState.get<string>(
      STATE_DISMISSED_VERSION,
    );
    if (dismissedVersion === latestVersion) {
      return;
    }
  }

  await showUpdateNotification(context, latestVersion, release.html_url);
}

/**
 * Register the update checker: schedule an automatic check on startup
 * and register the manual check command.
 */
export function registerUpdateChecker(context: ExtensionContext): void {
  // Register manual check command
  context.subscriptions.push(
    commands.registerCommand(`${PluginKey}.checkForUpdates`, () => {
      performUpdateCheck(context, true);
    }),
  );

  // Schedule automatic check after startup delay
  const timer = setTimeout(() => {
    performUpdateCheck(context, false);
  }, STARTUP_DELAY_MS);

  // Clean up timer on deactivation
  context.subscriptions.push({ dispose: () => clearTimeout(timer) });
}
