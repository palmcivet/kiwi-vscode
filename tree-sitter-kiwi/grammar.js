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
      $._space,
      $.identifier,
      ';',
    ),

    enum_declaration: $ => seq(
      'enum',
      $._space,
      $.identifier,
      $.enum_body,
    ),

    enum_body: $ => seq('{', repeat($.enum_field), '}'),

    enum_field: $ => seq(
      field('enum_field_name', $.identifier),
      '=',
      field('enum_field_value', $.number),
      ';',
    ),

    message_declaration: $ => seq(
      'message',
      $._space,
      $.identifier,
      $.message_body,
    ),

    message_body: $ => seq('{', repeat($.message_field), '}'),

    message_field: $ => seq(
      field('message_field_type', seq($.type_name, optional('[]'))),
      $._space,
      field('message_field_name', $.identifier),
      '=',
      field('message_field_value', $.number),
      optional($.deprecated_tag),
      ';',
    ),

    struct_declaration: $ => seq(
      'struct',
      $._space,
      $.identifier,
      $.struct_body,
    ),

    struct_body: $ => seq('{', repeat($.struct_field), '}'),

    struct_field: $ => seq(
      field('struct_field_type', seq($.type_name, optional('[]'))),
      $._space,
      field('struct_field_name', $.identifier),
      ';',
    ),

    type_name: $ => choice(
      $._primitive_type,
      $.identifier,
    ),

    deprecated_tag: $ => '[deprecated]',
    identifier: $ => token(/[A-Z_]\w*/i),
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
