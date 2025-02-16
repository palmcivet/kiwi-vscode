export function isPascalCase(s: string): boolean {
  return s[0] >= 'A' && s[0] <= 'Z' && !s.includes('_');
}

export function isCamelCase(s: string): boolean {
  return s[0] >= 'a' && s[0] <= 'z' && !s.includes('_');
}

export function isScreamingSnakeCase(s: string): boolean {
  if (!(s[0] >= 'A' && s[0] <= 'Z')) {
    return false;
  }

  for (const c of s) {
    if ((c >= 'A' && c <= 'Z') || c === '_' || (c >= '0' && c <= '9')) {
      continue;
    }

    return false;
  }

  return true;
}
