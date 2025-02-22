/* eslint-disable no-cond-assign */
import type { Definition, DefinitionKind, Field, Schema, Token } from './schema';
import { combineRanges, endOfRange, quote } from '@server/helper';
import { sentenceCase } from 'change-case';
import { createError, KiwiParseError } from './error';

// Native types supported by the Kiwi
export const NativeTypes = [
  'bool',
  'byte',
  'float',
  'int',
  'int64',
  'string',
  'uint',
  'uint64',
];

// These are special names on the object returned by compileSchema()
const ReservedNames = [
  'ByteBuffer',
  'package',
  'enum',
  'struct',
  'message',
  ...NativeTypes,
];

// Regular expressions for lexical analysis
const regex
  = /((?:-|\b)\d+\b|[=;{}]|\[\]|\[deprecated\]|\b[A-Za-z_]\w*\b|\/\/.*|\s+)/g;
const identifier = /^[A-Z_]\w*$/i;
const whitespace = /^\/\/.*|\s+$/;
const equals = /^=$/;
const endOfFile = /^$/;
const semicolon = /^;$/;
const integer = /^-?\d+$/;
const leftBrace = /^\{$/;
const rightBrace = /^\}$/;
const arrayToken = /^\[\]$/;
const enumKeyword = /^enum$/;
const structKeyword = /^struct$/;
const messageKeyword = /^message$/;
const packageKeyword = /^package$/;
const deprecatedToken = /^\[deprecated\]$/;

/**
 * Performs lexical analysis on the input text to generate tokens.
 * @param text The source code text to tokenize
 * @returns A tuple containing:
 * - An array of tokens extracted from the text
 * - An array of any syntax errors encountered during tokenization
 */
function tokenize(text: string): [Token[], KiwiParseError[]] {
  const errors: KiwiParseError[] = [];

  // Split text into tokens using the main regex pattern
  const parts = text.split(regex);
  const tokens: Token[] = [];
  let column = 0;
  let line = 0;

  for (let i = 0; i < parts.length; i++) {
    const part = parts[i];

    // Keep non-whitespace tokens
    if (i & 1) {
      if (!whitespace.test(part)) {
        tokens.push({
          text: part,
          span: {
            start: { line, character: column },
            end: { line, character: column + part.length },
          },
        });
      }
    }

    // Handle invalid tokens (syntax errors)
    else if (part !== '') {
      errors.push(
        createError(`Invalid token: ${quote(part)}`, {
          start: { line, character: column },
          end: { line, character: column + part.length },
        }),
      );
    }

    // Keep track of the line and column counts
    const lines = part.split('\n');
    if (lines.length > 1)
      column = 0;
    line += lines.length - 1;
    column += lines[lines.length - 1].length;
  }

  // Add end-of-file token
  tokens.push({
    text: '',
    span: {
      start: { line, character: column },
      end: { line, character: column },
    },
  });

  return [tokens, errors];
}

/**
 * Parses a sequence of tokens into a Kiwi schema.
 * Handles package declarations, enum/struct/message definitions, and their fields.
 * @param tokens Array of tokens from lexical analysis
 * @returns A tuple containing the parsed schema and any parsing errors
 */
function parse(tokens: Token[]): [Schema, KiwiParseError[]] {
  const errors: KiwiParseError[] = [];
  let index = 0;

  // Helper functions for token processing
  function current(): Token {
    return tokens[index];
  }

  function eat(test: RegExp): Token | null {
    const token = current();
    if (test.test(token.text)) {
      index++;
      return token;
    }
    return null;
  }

  function expect(test: RegExp, expected: string): Token {
    const token = current();
    if (!eat(test)) {
      throw new KiwiParseError(`Expected ${expected} but found ${quote(token.text)}`, token.span);
    }
    return token;
  }

  const definitions: Definition[] = [];
  let packageKeywordToken = null;
  let packageIdent = null;

  if ((packageKeywordToken = eat(packageKeyword))) {
    packageIdent = eat(identifier);

    const packageSemi = eat(semicolon);
    if (packageIdent) {
      if (
        packageIdent.text === 'enum'
        || packageIdent.text === 'struct'
        || packageIdent.text === 'message'
      ) {
        errors.push(
          createError('Expected package name', endOfRange(packageKeywordToken.span)),
        );
        index -= 1;
        packageIdent = null;
      }
      else if (!packageSemi) {
        errors.push(createError('Expected ";"', endOfRange(packageIdent.span)));
      }
    }
    else {
      errors.push(createError('Expected package name', endOfRange(current().span)));
    }
  }

  while (index < tokens.length && !eat(endOfFile)) {
    const fields: Field[] = [];
    let kind: DefinitionKind;
    let kindTok: Token | null;

    if ((kindTok = eat(enumKeyword))) {
      kind = 'ENUM';
    }
    else if ((kindTok = eat(structKeyword))) {
      kind = 'STRUCT';
    }
    else if ((kindTok = eat(messageKeyword))) {
      kind = 'MESSAGE';
    }
    else {
      const tok = current();
      errors.push(createError(`Unexpected token "${tok.text}"`, tok.span));
      index += 1;
      continue;
    }

    // All definitions start off the same
    let name: Token | null = current();

    if (!eat(identifier)) {
      name = null;
      errors.push(
        createError(
          `${sentenceCase(kind)} missing name`,
          combineRanges(kindTok.span, current().span),
        ),
      );
    }

    const openFieldsBrace = expect(leftBrace, '"{"');
    let closeFieldsBrace: Token | null;

    // Parse fields

    while (true) {
      closeFieldsBrace = eat(rightBrace);

      if (closeFieldsBrace) {
        break;
      }

      let type: Token | null = null;
      let isArray = false;
      let isDeprecated = false;

      // Enums don't have types
      if (kind !== 'ENUM') {
        type = current();
        expect(identifier, 'identifier');
        isArray = !!eat(arrayToken);
      }

      const field = current();
      expect(identifier, 'identifier');

      // Structs don't have explicit values
      let value: Token | null = null;
      if (kind !== 'STRUCT') {
        let eqError;
        if (!eat(equals)) {
          eqError = createError('Expected "="', current().span);
        }

        value = current();

        if (!eat(integer)) {
          if (eqError) {
            eqError.message = `Expected id assignment. e.g. \`${
              type ? `${type.text} ` : ''
            }${field.text} = 1\``;
          }
          else {
            eqError = createError(
              `Expected integer id. found ${quote(current().text)}`,
              current().span,
            );
          }
        }

        if (eqError) {
          errors.push(eqError);
        }
        else if (`${+value.text | 0}` !== value.text) {
          errors.push(
            createError(`Invalid integer ${quote(value.text)}`, current().span),
          );
        }
      }

      const deprecated = current();
      if (eat(deprecatedToken)) {
        if (kind !== 'MESSAGE') {
          errors.push(createError('Can only deprecate message fields', deprecated.span));
        }
        else {
          isDeprecated = true;
        }
      }
      else if (kind !== 'ENUM') {
        let deprecatedErrorToken = null;
        if ((deprecatedErrorToken = eat(/\[|\]/))) {
          errors.push(createError('Expected `[deprecated]`', deprecatedErrorToken.span));
        }
        else if ((deprecatedErrorToken = eat(/deprecated/))) {
          errors.push(
            createError('Did you mean `[deprecated]`?', deprecatedErrorToken.span),
          );
        }
      }

      let semicolonSpan;

      if (kind === 'STRUCT' && current().text === '=') {
        let range = current().span;
        expect(equals, '"="');

        let next;
        if ((next = eat(integer))) {
          range = combineRanges(range, next.span);
        }
        semicolonSpan = eat(semicolon)?.span;

        errors.push(createError('Struct fields can\'t have explicit ids.', range));
      }

      if (!eat(semicolon)) {
        const range = value?.span ?? field.span;
        errors.push(createError('Expected ";"', endOfRange(range)));
      }

      const fullSpan = combineRanges(
        field.span,
        type?.span || field.span,
        value?.span || field.span,
        semicolonSpan || field.span,
      );

      fields.push({
        span: fullSpan,
        name: field.text,
        nameSpan: field.span,
        type: type?.text,
        typeSpan: type?.span,
        isArray,
        isDeprecated,
        deprecatedSpan: deprecated.span,
        value: value !== null ? +value.text | 0 : fields.length + 1,
        valueSpan: value?.span || fullSpan,
      });
    }

    if (!name) {
      continue;
    }

    definitions.push({
      keywordSpan: kindTok.span,
      defSpan: combineRanges(kindTok.span, closeFieldsBrace.span),
      name: name.text,
      nameSpan: name.span,
      kind,
      fields,
      fieldsSpan: combineRanges(openFieldsBrace.span, closeFieldsBrace.span),
    });
  }

  return [
    {
      package: packageIdent,
      definitions,
    },
    errors,
  ];
}

/**
 * Performs semantic validation on the parsed schema.
 * Checks for:
 * - Type existence and conflicts with native types
 * - Duplicate definitions
 * - Reserved name usage
 * - Field type validity
 * - Duplicate field names/IDs
 * - Valid field ID ranges
 * - Recursive struct nesting
 * @param root The schema to validate
 * @returns Array of validation errors
 */
function verify(root: Schema): KiwiParseError[] {
  const errors: KiwiParseError[] = [];
  const definedTypes = NativeTypes.slice();
  const definitions: { [name: string]: Definition } = {};

  // First pass: Check for type conflicts and duplicates
  for (let i = 0; i < root.definitions.length; i++) {
    const definition = root.definitions[i];

    // Check for conflicts with native types
    const nativeDefinition = NativeTypes.find(v => v === definition.name);
    if (nativeDefinition) {
      errors.push(
        createError(
          `The type ${quote(definition.name)} conflicts with a native type`,
          definition.nameSpan,
        ),
      );
    }

    const duplicateDefinitionIdx = definedTypes.indexOf(definition.name);
    if (duplicateDefinitionIdx !== -1) {
      errors.push(
        createError(
          `The type ${quote(definition.name)} is defined twice`,
          definition.nameSpan,
          {
            message: 'Also defined here',
            span: definitions[definedTypes[duplicateDefinitionIdx]].nameSpan,
          },
        ),
      );
    }
    if (ReservedNames.includes(definition.name)) {
      errors.push(
        createError(
          `The type name ${quote(definition.name)} is reserved`,
          definition.nameSpan,
        ),
      );
    }
    definedTypes.push(definition.name);
    definitions[definition.name] = definition;
  }

  // Check fields
  for (let i = 0; i < root.definitions.length; i++) {
    const definition = root.definitions[i];
    const fields = definition.fields;

    if (fields.length === 0) {
      continue;
    }

    if (definition.kind !== 'ENUM') {
      // Check types
      for (let j = 0; j < fields.length; j++) {
        const field = fields[j];
        if (!definedTypes.includes(field.type!)) {
          errors.push(
            createError(
              `The type ${quote(field.type!)} doesn't exist.`,
              field.typeSpan!,
            ),
          );
        }
      }
    }

    // Check values
    const checkedFields: Field[] = [];
    for (let j = 0; j < fields.length; j++) {
      const field = fields[j];

      const duplicateName = checkedFields.find(f => f.name === field.name);
      if (duplicateName) {
        errors.push(
          createError(
            `The name for field ${quote(field.name)} is used twice`,
            field.nameSpan,
            { message: 'Also used here', span: duplicateName.nameSpan },
          ),
        );
      }

      const duplicateValue = checkedFields.find(f => f.value === field.value);
      let fieldError;
      if (duplicateValue) {
        fieldError = createError(
          `The id for field ${quote(field.name)} is used twice`,
          field.valueSpan,
          { message: 'Also used here', span: duplicateValue.valueSpan },
          'invalid id',
        );
      }
      else if (
        (definition.kind === 'ENUM' && field.value < 0)
        || (definition.kind !== 'ENUM' && field.value <= 0)
      ) {
        fieldError = createError(
          `The id for field ${quote(field.name)} must be positive`,
          field.valueSpan,
          undefined,
          'invalid id',
        );
      }
      else if (definition.kind !== 'ENUM' && field.value > fields.length) {
        fieldError = createError(
          `The id for field ${
            quote(field.name)
          } cannot be larger than ${
            fields.length}`,
          field.valueSpan,
          undefined,
          'invalid id',
        );
      }

      if (fieldError) {
        errors.push(fieldError);
      }

      checkedFields.push(field);
    }
  }

  // Check that structs don't contain themselves
  const state: { [name: string]: number } = {};
  const check = (name: string): boolean => {
    const definition = definitions[name];
    if (definition && definition.kind === 'STRUCT') {
      if (state[name] === 1) {
        errors.push(
          createError(
            `Recursive nesting of ${quote(name)} is not allowed`,
            definition.nameSpan,
          ),
        );
      }
      if (state[name] !== 2 && definition) {
        state[name] = 1;
        const fields = definition.fields;
        for (let i = 0; i < fields.length; i++) {
          const field = fields[i];
          if (!field.isArray) {
            check(field.type!);
          }
        }
        state[name] = 2;
      }
    }
    return true;
  };
  for (let i = 0; i < root.definitions.length; i++) {
    check(root.definitions[i].name);
  }

  return errors;
}

/**
 * Parses and validates a Kiwi schema text through three main steps:
 * 1. Lexical analysis (tokenization)
 * 2. Syntax parsing
 * 3. Semantic validation
 *
 * Note: During parsing, if a fatal error is encountered (e.g., missing required syntax elements),
 * the parser will throw a KiwiParseError through the expect() function.
 *
 * @param text The source code text of the Kiwi schema to parse
 * @returns A tuple containing:
 * - The parsed and validated schema
 * - An array of any errors encountered during tokenization, parsing, or validation
 */
export function parseSchema(text: string): [Schema, KiwiParseError[]] {
  const [tokens, tokenErrors] = tokenize(text);
  const [schema, parseErrors] = parse(tokens);
  const validateErrors = verify(schema);
  return [schema, [...tokenErrors, ...parseErrors, ...validateErrors]];
}
