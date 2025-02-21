/* eslint-disable unused-imports/no-unused-vars */
/* eslint-disable no-undef */

/// <reference types="tree-sitter-cli/dsl" />

module.exports = grammar({
  name: 'kiwi',

  word: $ => $.identifier,

  // 注释保持在前
  rules: {
    source_file: $ => seq(
      optional(seq(
        repeat($.comment),
        $.package_declaration,
      )),
      repeat(seq(
        repeat($.comment),
        $.include_directive,
      )),
      repeat(seq(
        repeat($.comment),
        choice(
          $.enum_definition,
          $.message_definition,
        ),
      )),
      repeat($.comment),
    ),

    include_directive: $ => seq(
      '/// @include ',
      $.path,
    ),

    path: $ => choice(
      seq('"', $.dir, '"'),
      seq('\'', $.dir, '\''),
      /\S+/,
    ),

    comment: $ => seq('//', /.*/),

    package_declaration: $ => seq(
      'package',
      $.space,
      $.identifier,
      ';',
    ),

    enum_definition: $ => seq(
      'enum',
      $.space,
      $.identifier,
      repeat($.comment),
      $.enum_body,
    ),

    enum_body: $ => seq('{', repeat(choice($.enum_field, $.comment)), '}'),

    enum_field: $ => seq(
      field('enum_field_name', $.identifier),
      '=',
      field('enum_field_value', $.number),
      ';',
    ),

    message_definition: $ => seq(
      'message',
      $.space,
      $.identifier,
      repeat($.comment),
      $.message_body,
    ),

    message_body: $ => seq('{', repeat(choice($.message_field, $.comment)), '}'),

    message_field: $ => seq(
      field('message_field_type', seq($.type_name, optional('[]'))),
      $.space,
      field('message_field_name', $.identifier),
      '=',
      field('message_field_value', $.number),
      optional($.deprecated_tag),
      ';',
    ),

    type_name: $ => choice(
      'bool',
      'byte',
      'int32',
      'int64',
      'uint32',
      'uint64',
      'float',
      'double',
      'string',
      $.identifier,
    ),

    deprecated_tag: $ => choice(
      '[deprecated]',
      seq('[deprecated(', /[^)]+/, ')]'),
    ),

    identifier: $ => /[A-Z_]\w*/i,
    number: $ => /\d+/,
    dir: $ => /[\w\-/.]+/,
    space: $ => repeat1(/\s/),
  },
});
