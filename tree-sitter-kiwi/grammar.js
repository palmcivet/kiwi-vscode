/* eslint-disable unused-imports/no-unused-vars */
/* eslint-disable no-undef */

/// <reference types="tree-sitter-cli/dsl" />

module.exports = grammar({
  name: 'kiwi',

  word: $ => $.identifier,

  extras: $ => [
    /\s/,
    $.comment,
  ],

  rules: {
    source_file: $ => seq(
      optional($.package_declaration),
      repeat($.include_directive),
      repeat(choice(
        $.enum_declaration,
        $.message_declaration,
        $.struct_declaration,
      )),
    ),

    include_directive: $ => seq(
      '/// @include ',
      $.path,
    ),

    comment: $ => choice(
      seq('//', /.*/),
    ),

    package_declaration: $ => seq(
      'package',
      $.identifier,
      ';',
    ),

    enum_declaration: $ => seq(
      'enum',
      $.identifier,
      $.enum_body,
    ),

    enum_body: $ => seq('{', repeat($.enum_field), '}'),

    enum_field: $ => seq(
      $.enum_field_name,
      '=',
      $.enum_field_value,
      ';',
    ),
    enum_field_name: $ => $.identifier,
    enum_field_value: $ => $.number,

    message_declaration: $ => seq(
      'message',
      $.identifier,
      $.message_body,
    ),

    message_body: $ => seq('{', repeat($.message_field), '}'),

    message_field: $ => seq(
      $.message_field_type,
      $.message_field_name,
      '=',
      $.message_field_value,
      ';',
    ),
    message_field_type: $ => $.type_name,
    message_field_name: $ => $.identifier,
    message_field_value: $ => seq($.number, optional($.deprecated_tag)),

    struct_declaration: $ => seq(
      'struct',
      $.identifier,
      $.struct_body,
    ),

    struct_body: $ => seq('{', repeat($.struct_field), '}'),

    struct_field: $ => seq(
      $.struct_field_type,
      $.struct_field_name,
      ';',
    ),
    struct_field_type: $ => $.type_name,
    struct_field_name: $ => $.identifier,

    type_name: $ => seq(
      choice($._primitive_type, $.identifier),
      optional($.array),
    ),
    deprecated_tag: $ => token('[deprecated]'),
    identifier: $ => token(/[A-Z_]\w*/i),
    array: $ => token('[]'),
    number: $ => token(/\d+/),
    path: $ => choice(
      seq('"', $._dir, '"'),
      seq('\'', $._dir, '\''),
      /\S+/,
    ),

    _space: $ => repeat1(/\s/),
    _dir: $ => token(/[\w\-/.]+/),
    _primitive_type: $ => token(choice(
      'bool',
      'byte',
      'int32',
      'int64',
      'uint32',
      'uint64',
      'float',
      'double',
      'string',
    )),
  },
});
