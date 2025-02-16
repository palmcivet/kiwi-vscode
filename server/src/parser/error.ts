import type { Range } from 'vscode-languageserver/node';

type ErrorKind = 'invalid id';

interface RelatedInformation {
  span: Range;
  message: string;
}

export class KiwiParseError extends Error {
  constructor(
    message: string,
    public readonly range: Range,
    public readonly relatedInformation?: RelatedInformation,
    public readonly errorKind?: ErrorKind,
  ) {
    super(message);
  }
}

export function createError(
  text: string,
  range: Range,
  relatedInformation?: RelatedInformation,
  errorKind?: ErrorKind,
): KiwiParseError {
  return new KiwiParseError(text, range, relatedInformation, errorKind);
}
