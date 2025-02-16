import * as assert from 'node:assert';
import { isCamelCase, isPascalCase, isScreamingSnakeCase } from '../helper';

describe('casing utilities', () => {
  it('isCamelCase', () => {
    assert.strictEqual(isCamelCase('camelCase'), true);
    assert.strictEqual(isCamelCase('myVariable'), true);
    assert.strictEqual(isCamelCase('abc'), true);

    assert.strictEqual(isCamelCase('CamelCase'), false);
    assert.strictEqual(isCamelCase('snake_case'), false);
    assert.strictEqual(isCamelCase('SCREAMING_CASE'), false);
    assert.strictEqual(isCamelCase(''), false);
  });

  it('isPascalCase', () => {
    assert.strictEqual(isPascalCase('PascalCase'), true);
    assert.strictEqual(isPascalCase('MyClass'), true);
    assert.strictEqual(isPascalCase('Abc'), true);

    assert.strictEqual(isPascalCase('camelCase'), false);
    assert.strictEqual(isPascalCase('snake_case'), false);
    assert.strictEqual(isPascalCase('SCREAMING_CASE'), false);
    assert.strictEqual(isPascalCase(''), false);
  });

  it('isScreamingSnakeCase', () => {
    assert.strictEqual(isScreamingSnakeCase('SCREAMING_SNAKE_CASE'), true);
    assert.strictEqual(isScreamingSnakeCase('MY_CONSTANT'), true);
    assert.strictEqual(isScreamingSnakeCase('ABC'), true);
    assert.strictEqual(isScreamingSnakeCase('MY_CONSTANT_123'), true);

    assert.strictEqual(isScreamingSnakeCase('camelCase'), false);
    assert.strictEqual(isScreamingSnakeCase('PascalCase'), false);
    assert.strictEqual(isScreamingSnakeCase('snake_case'), false);
    assert.strictEqual(isScreamingSnakeCase(''), false);
    assert.strictEqual(isScreamingSnakeCase('MY_constant'), false);
  });
});
