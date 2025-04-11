#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 88
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 43
#define ALIAS_COUNT 0
#define TOKEN_COUNT 22
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 7
#define MAX_ALIAS_SEQUENCE_LENGTH 8
#define PRODUCTION_ID_COUNT 6

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SLASH_SLASH_SLASH_ATinclude = 2,
  anon_sym_SLASH_SLASH = 3,
  aux_sym_comment_token1 = 4,
  anon_sym_package = 5,
  anon_sym_SEMI = 6,
  anon_sym_enum = 7,
  anon_sym_LBRACE = 8,
  anon_sym_RBRACE = 9,
  anon_sym_EQ = 10,
  anon_sym_message = 11,
  anon_sym_LBRACK_RBRACK = 12,
  anon_sym_struct = 13,
  sym_deprecated_tag = 14,
  sym_number = 15,
  anon_sym_DQUOTE = 16,
  anon_sym_SQUOTE = 17,
  aux_sym_path_token1 = 18,
  aux_sym__space_token1 = 19,
  sym__dir = 20,
  sym__primitive_type = 21,
  sym_source_file = 22,
  sym_include_directive = 23,
  sym_comment = 24,
  sym_package_declaration = 25,
  sym_enum_declaration = 26,
  sym_enum_body = 27,
  sym_enum_field = 28,
  sym_message_declaration = 29,
  sym_message_body = 30,
  sym_message_field = 31,
  sym_struct_declaration = 32,
  sym_struct_body = 33,
  sym_struct_field = 34,
  sym_type_name = 35,
  sym_path = 36,
  aux_sym__space = 37,
  aux_sym_source_file_repeat1 = 38,
  aux_sym_source_file_repeat2 = 39,
  aux_sym_enum_body_repeat1 = 40,
  aux_sym_message_body_repeat1 = 41,
  aux_sym_struct_body_repeat1 = 42,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SLASH_SLASH_SLASH_ATinclude] = "/// @include ",
  [anon_sym_SLASH_SLASH] = "//",
  [aux_sym_comment_token1] = "comment_token1",
  [anon_sym_package] = "package",
  [anon_sym_SEMI] = ";",
  [anon_sym_enum] = "enum",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_EQ] = "=",
  [anon_sym_message] = "message",
  [anon_sym_LBRACK_RBRACK] = "[]",
  [anon_sym_struct] = "struct",
  [sym_deprecated_tag] = "deprecated_tag",
  [sym_number] = "number",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_path_token1] = "path_token1",
  [aux_sym__space_token1] = "_space_token1",
  [sym__dir] = "_dir",
  [sym__primitive_type] = "_primitive_type",
  [sym_source_file] = "source_file",
  [sym_include_directive] = "include_directive",
  [sym_comment] = "comment",
  [sym_package_declaration] = "package_declaration",
  [sym_enum_declaration] = "enum_declaration",
  [sym_enum_body] = "enum_body",
  [sym_enum_field] = "enum_field",
  [sym_message_declaration] = "message_declaration",
  [sym_message_body] = "message_body",
  [sym_message_field] = "message_field",
  [sym_struct_declaration] = "struct_declaration",
  [sym_struct_body] = "struct_body",
  [sym_struct_field] = "struct_field",
  [sym_type_name] = "type_name",
  [sym_path] = "path",
  [aux_sym__space] = "_space",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_source_file_repeat2] = "source_file_repeat2",
  [aux_sym_enum_body_repeat1] = "enum_body_repeat1",
  [aux_sym_message_body_repeat1] = "message_body_repeat1",
  [aux_sym_struct_body_repeat1] = "struct_body_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SLASH_SLASH_SLASH_ATinclude] = anon_sym_SLASH_SLASH_SLASH_ATinclude,
  [anon_sym_SLASH_SLASH] = anon_sym_SLASH_SLASH,
  [aux_sym_comment_token1] = aux_sym_comment_token1,
  [anon_sym_package] = anon_sym_package,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_enum] = anon_sym_enum,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_message] = anon_sym_message,
  [anon_sym_LBRACK_RBRACK] = anon_sym_LBRACK_RBRACK,
  [anon_sym_struct] = anon_sym_struct,
  [sym_deprecated_tag] = sym_deprecated_tag,
  [sym_number] = sym_number,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_path_token1] = aux_sym_path_token1,
  [aux_sym__space_token1] = aux_sym__space_token1,
  [sym__dir] = sym__dir,
  [sym__primitive_type] = sym__primitive_type,
  [sym_source_file] = sym_source_file,
  [sym_include_directive] = sym_include_directive,
  [sym_comment] = sym_comment,
  [sym_package_declaration] = sym_package_declaration,
  [sym_enum_declaration] = sym_enum_declaration,
  [sym_enum_body] = sym_enum_body,
  [sym_enum_field] = sym_enum_field,
  [sym_message_declaration] = sym_message_declaration,
  [sym_message_body] = sym_message_body,
  [sym_message_field] = sym_message_field,
  [sym_struct_declaration] = sym_struct_declaration,
  [sym_struct_body] = sym_struct_body,
  [sym_struct_field] = sym_struct_field,
  [sym_type_name] = sym_type_name,
  [sym_path] = sym_path,
  [aux_sym__space] = aux_sym__space,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_source_file_repeat2] = aux_sym_source_file_repeat2,
  [aux_sym_enum_body_repeat1] = aux_sym_enum_body_repeat1,
  [aux_sym_message_body_repeat1] = aux_sym_message_body_repeat1,
  [aux_sym_struct_body_repeat1] = aux_sym_struct_body_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SLASH_SLASH_SLASH_ATinclude] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH_SLASH] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_comment_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_package] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_enum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_message] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_struct] = {
    .visible = true,
    .named = false,
  },
  [sym_deprecated_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_path_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__space_token1] = {
    .visible = false,
    .named = false,
  },
  [sym__dir] = {
    .visible = false,
    .named = true,
  },
  [sym__primitive_type] = {
    .visible = false,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_include_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_package_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_body] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_field] = {
    .visible = true,
    .named = true,
  },
  [sym_message_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_message_body] = {
    .visible = true,
    .named = true,
  },
  [sym_message_field] = {
    .visible = true,
    .named = true,
  },
  [sym_struct_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_struct_body] = {
    .visible = true,
    .named = true,
  },
  [sym_struct_field] = {
    .visible = true,
    .named = true,
  },
  [sym_type_name] = {
    .visible = true,
    .named = true,
  },
  [sym_path] = {
    .visible = true,
    .named = true,
  },
  [aux_sym__space] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enum_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_message_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_struct_body_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_enum_field_name = 1,
  field_enum_field_value = 2,
  field_message_field_name = 3,
  field_message_field_type = 4,
  field_message_field_value = 5,
  field_struct_field_name = 6,
  field_struct_field_type = 7,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_enum_field_name] = "enum_field_name",
  [field_enum_field_value] = "enum_field_value",
  [field_message_field_name] = "message_field_name",
  [field_message_field_type] = "message_field_type",
  [field_message_field_value] = "message_field_value",
  [field_struct_field_name] = "struct_field_name",
  [field_struct_field_type] = "struct_field_type",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
  [2] = {.index = 2, .length = 2},
  [3] = {.index = 4, .length = 3},
  [4] = {.index = 7, .length = 3},
  [5] = {.index = 10, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_enum_field_name, 0},
    {field_enum_field_value, 2},
  [2] =
    {field_struct_field_name, 2},
    {field_struct_field_type, 0},
  [4] =
    {field_struct_field_name, 3},
    {field_struct_field_type, 0},
    {field_struct_field_type, 1},
  [7] =
    {field_message_field_name, 2},
    {field_message_field_type, 0},
    {field_message_field_value, 4},
  [10] =
    {field_message_field_name, 3},
    {field_message_field_type, 0},
    {field_message_field_type, 1},
    {field_message_field_value, 5},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 73,
  [74] = 74,
  [75] = 75,
  [76] = 76,
  [77] = 77,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(28);
      ADVANCE_MAP(
        '"', 96,
        '\'', 98,
        '/', 103,
        ';', 38,
        '=', 41,
        '[', 8,
        'b', 76,
        'd', 72,
        'f', 66,
        'i', 70,
        's', 83,
        'u', 58,
        '{', 39,
        '}', 40,
        '-', 104,
        '.', 104,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(102);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(7);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(29);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(97);
      if (lookahead == '\'') ADVANCE(99);
      if (lookahead == '/') ADVANCE(100);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(102);
      if (lookahead != 0) ADVANCE(101);
      END_STATE();
    case 4:
      if (lookahead == '/') ADVANCE(103);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(102);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(104);
      END_STATE();
    case 5:
      if (lookahead == '/') ADVANCE(31);
      END_STATE();
    case 6:
      if (lookahead == '/') ADVANCE(30);
      END_STATE();
    case 7:
      if (lookahead == '@') ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == ']') ADVANCE(42);
      if (lookahead == 'd') ADVANCE(15);
      END_STATE();
    case 9:
      if (lookahead == ']') ADVANCE(43);
      END_STATE();
    case 10:
      if (lookahead == 'a') ADVANCE(24);
      END_STATE();
    case 11:
      if (lookahead == 'c') ADVANCE(10);
      END_STATE();
    case 12:
      if (lookahead == 'c') ADVANCE(20);
      END_STATE();
    case 13:
      if (lookahead == 'd') ADVANCE(9);
      END_STATE();
    case 14:
      if (lookahead == 'd') ADVANCE(18);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(11);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(13);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(2);
      END_STATE();
    case 19:
      if (lookahead == 'i') ADVANCE(21);
      END_STATE();
    case 20:
      if (lookahead == 'l') ADVANCE(25);
      END_STATE();
    case 21:
      if (lookahead == 'n') ADVANCE(12);
      END_STATE();
    case 22:
      if (lookahead == 'p') ADVANCE(23);
      END_STATE();
    case 23:
      if (lookahead == 'r') ADVANCE(16);
      END_STATE();
    case 24:
      if (lookahead == 't') ADVANCE(17);
      END_STATE();
    case 25:
      if (lookahead == 'u') ADVANCE(14);
      END_STATE();
    case 26:
      if (eof) ADVANCE(28);
      ADVANCE_MAP(
        '"', 96,
        '\'', 98,
        '/', 6,
        ';', 38,
        '=', 41,
        '[', 8,
        'b', 78,
        'd', 74,
        'f', 67,
        'i', 71,
        's', 87,
        'u', 59,
        '{', 39,
        '}', 40,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(102);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 27:
      if (eof) ADVANCE(28);
      if (lookahead == '/') ADVANCE(5);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(102);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH_ATinclude);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(1);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(104);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(101);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(37);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '\n') ADVANCE(102);
      if (lookahead == '/') ADVANCE(36);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(37);
      if (lookahead != 0) ADVANCE(37);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '/') ADVANCE(34);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(37);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(37);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_LBRACK_RBRACK);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_deprecated_tag);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(44);
      if (lookahead == '6') ADVANCE(48);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(45);
      if (lookahead == '6') ADVANCE(49);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(82);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(86);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(63);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(70);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(71);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(68);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(69);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(54);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(73);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(75);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(56);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(85);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(89);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(90);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(50);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(91);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(77);
      if (lookahead == 'y') ADVANCE(84);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(62);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(79);
      if (lookahead == 'y') ADVANCE(88);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(60);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(92);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(80);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(54);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(46);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(93);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(81);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(52);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(53);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_identifier);
      if (('-' <= lookahead && lookahead <= '/')) ADVANCE(104);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(92);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(93);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      if (('-' <= lookahead && lookahead <= '/') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(104);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(101);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(101);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(aux_sym_path_token1);
      if (lookahead == '/') ADVANCE(33);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(101);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(aux_sym_path_token1);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(101);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(aux_sym__space_token1);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym__dir);
      if (lookahead == '/') ADVANCE(32);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(104);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym__dir);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(104);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'e') ADVANCE(1);
      if (lookahead == 'm') ADVANCE(2);
      if (lookahead == 'p') ADVANCE(3);
      if (lookahead == 's') ADVANCE(4);
      END_STATE();
    case 1:
      if (lookahead == 'n') ADVANCE(5);
      END_STATE();
    case 2:
      if (lookahead == 'e') ADVANCE(6);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(7);
      END_STATE();
    case 4:
      if (lookahead == 't') ADVANCE(8);
      END_STATE();
    case 5:
      if (lookahead == 'u') ADVANCE(9);
      END_STATE();
    case 6:
      if (lookahead == 's') ADVANCE(10);
      END_STATE();
    case 7:
      if (lookahead == 'c') ADVANCE(11);
      END_STATE();
    case 8:
      if (lookahead == 'r') ADVANCE(12);
      END_STATE();
    case 9:
      if (lookahead == 'm') ADVANCE(13);
      END_STATE();
    case 10:
      if (lookahead == 's') ADVANCE(14);
      END_STATE();
    case 11:
      if (lookahead == 'k') ADVANCE(15);
      END_STATE();
    case 12:
      if (lookahead == 'u') ADVANCE(16);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_enum);
      END_STATE();
    case 14:
      if (lookahead == 'a') ADVANCE(17);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 16:
      if (lookahead == 'c') ADVANCE(19);
      END_STATE();
    case 17:
      if (lookahead == 'g') ADVANCE(20);
      END_STATE();
    case 18:
      if (lookahead == 'g') ADVANCE(21);
      END_STATE();
    case 19:
      if (lookahead == 't') ADVANCE(22);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(23);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(24);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_struct);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_message);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_package);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 27},
  [2] = {.lex_state = 27},
  [3] = {.lex_state = 27},
  [4] = {.lex_state = 27},
  [5] = {.lex_state = 26},
  [6] = {.lex_state = 26},
  [7] = {.lex_state = 26},
  [8] = {.lex_state = 26},
  [9] = {.lex_state = 27},
  [10] = {.lex_state = 26},
  [11] = {.lex_state = 26},
  [12] = {.lex_state = 26},
  [13] = {.lex_state = 26},
  [14] = {.lex_state = 26},
  [15] = {.lex_state = 26},
  [16] = {.lex_state = 27},
  [17] = {.lex_state = 27},
  [18] = {.lex_state = 27},
  [19] = {.lex_state = 27},
  [20] = {.lex_state = 27},
  [21] = {.lex_state = 26},
  [22] = {.lex_state = 3},
  [23] = {.lex_state = 26},
  [24] = {.lex_state = 26},
  [25] = {.lex_state = 26},
  [26] = {.lex_state = 26},
  [27] = {.lex_state = 26},
  [28] = {.lex_state = 26},
  [29] = {.lex_state = 26},
  [30] = {.lex_state = 26},
  [31] = {.lex_state = 26},
  [32] = {.lex_state = 26},
  [33] = {.lex_state = 26},
  [34] = {.lex_state = 26},
  [35] = {.lex_state = 26},
  [36] = {.lex_state = 26},
  [37] = {.lex_state = 26},
  [38] = {.lex_state = 26},
  [39] = {.lex_state = 26},
  [40] = {.lex_state = 26},
  [41] = {.lex_state = 26},
  [42] = {.lex_state = 26},
  [43] = {.lex_state = 26},
  [44] = {.lex_state = 26},
  [45] = {.lex_state = 26},
  [46] = {.lex_state = 26},
  [47] = {.lex_state = 26},
  [48] = {.lex_state = 26},
  [49] = {.lex_state = 26},
  [50] = {.lex_state = 26},
  [51] = {.lex_state = 26},
  [52] = {.lex_state = 26},
  [53] = {.lex_state = 26},
  [54] = {.lex_state = 26},
  [55] = {.lex_state = 26},
  [56] = {.lex_state = 26},
  [57] = {.lex_state = 26},
  [58] = {.lex_state = 26},
  [59] = {.lex_state = 26},
  [60] = {.lex_state = 26},
  [61] = {.lex_state = 26},
  [62] = {.lex_state = 4},
  [63] = {.lex_state = 26},
  [64] = {.lex_state = 26},
  [65] = {.lex_state = 26},
  [66] = {.lex_state = 26},
  [67] = {.lex_state = 26},
  [68] = {.lex_state = 26},
  [69] = {.lex_state = 26},
  [70] = {.lex_state = 26},
  [71] = {.lex_state = 26},
  [72] = {.lex_state = 26},
  [73] = {.lex_state = 35},
  [74] = {.lex_state = 26},
  [75] = {.lex_state = 26},
  [76] = {.lex_state = 26},
  [77] = {.lex_state = 4},
  [78] = {.lex_state = 26},
  [79] = {.lex_state = 26},
  [80] = {.lex_state = 26},
  [81] = {.lex_state = 26},
  [82] = {.lex_state = 26},
  [83] = {.lex_state = 26},
  [84] = {.lex_state = 26},
  [85] = {.lex_state = 26},
  [86] = {.lex_state = 26},
  [87] = {(TSStateId)(-1)},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [sym_comment] = STATE(0),
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SLASH_SLASH] = ACTIONS(3),
    [anon_sym_package] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_message] = ACTIONS(1),
    [anon_sym_LBRACK_RBRACK] = ACTIONS(1),
    [anon_sym_struct] = ACTIONS(1),
    [sym_deprecated_tag] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [aux_sym__space_token1] = ACTIONS(5),
    [sym__dir] = ACTIONS(1),
    [sym__primitive_type] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(66),
    [sym_include_directive] = STATE(18),
    [sym_comment] = STATE(1),
    [sym_package_declaration] = STATE(3),
    [sym_enum_declaration] = STATE(27),
    [sym_message_declaration] = STATE(27),
    [sym_struct_declaration] = STATE(27),
    [aux_sym_source_file_repeat1] = STATE(4),
    [aux_sym_source_file_repeat2] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(7),
    [anon_sym_SLASH_SLASH_SLASH_ATinclude] = ACTIONS(9),
    [anon_sym_SLASH_SLASH] = ACTIONS(3),
    [anon_sym_package] = ACTIONS(11),
    [anon_sym_enum] = ACTIONS(13),
    [anon_sym_message] = ACTIONS(15),
    [anon_sym_struct] = ACTIONS(17),
    [aux_sym__space_token1] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      sym_comment,
    STATE(7), 1,
      aux_sym_source_file_repeat2,
    STATE(9), 1,
      aux_sym_source_file_repeat1,
    STATE(18), 1,
      sym_include_directive,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [39] = 12,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(21), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      aux_sym_source_file_repeat1,
    STATE(3), 1,
      sym_comment,
    STATE(6), 1,
      aux_sym_source_file_repeat2,
    STATE(18), 1,
      sym_include_directive,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [78] = 12,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(21), 1,
      ts_builtin_sym_end,
    STATE(4), 1,
      sym_comment,
    STATE(6), 1,
      aux_sym_source_file_repeat2,
    STATE(9), 1,
      aux_sym_source_file_repeat1,
    STATE(18), 1,
      sym_include_directive,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [117] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(21), 1,
      ts_builtin_sym_end,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(5), 1,
      sym_comment,
    STATE(8), 1,
      aux_sym_source_file_repeat2,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [147] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(6), 1,
      sym_comment,
    STATE(8), 1,
      aux_sym_source_file_repeat2,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [177] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(17), 1,
      anon_sym_struct,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(25), 1,
      ts_builtin_sym_end,
    STATE(7), 1,
      sym_comment,
    STATE(8), 1,
      aux_sym_source_file_repeat2,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [207] = 8,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(27), 1,
      ts_builtin_sym_end,
    ACTIONS(29), 1,
      anon_sym_enum,
    ACTIONS(32), 1,
      anon_sym_message,
    ACTIONS(35), 1,
      anon_sym_struct,
    STATE(8), 2,
      sym_comment,
      aux_sym_source_file_repeat2,
    STATE(27), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [235] = 6,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(40), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    STATE(18), 1,
      sym_include_directive,
    STATE(9), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(38), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [258] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(43), 1,
      sym_identifier,
    ACTIONS(45), 1,
      anon_sym_RBRACE,
    ACTIONS(47), 1,
      sym__primitive_type,
    STATE(10), 1,
      sym_comment,
    STATE(12), 1,
      aux_sym_message_body_repeat1,
    STATE(37), 1,
      sym_message_field,
    STATE(47), 1,
      sym_type_name,
  [286] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(43), 1,
      sym_identifier,
    ACTIONS(47), 1,
      sym__primitive_type,
    ACTIONS(49), 1,
      anon_sym_RBRACE,
    STATE(11), 1,
      sym_comment,
    STATE(13), 1,
      aux_sym_struct_body_repeat1,
    STATE(38), 1,
      sym_struct_field,
    STATE(49), 1,
      sym_type_name,
  [314] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(43), 1,
      sym_identifier,
    ACTIONS(47), 1,
      sym__primitive_type,
    ACTIONS(51), 1,
      anon_sym_RBRACE,
    STATE(12), 1,
      sym_comment,
    STATE(14), 1,
      aux_sym_message_body_repeat1,
    STATE(37), 1,
      sym_message_field,
    STATE(47), 1,
      sym_type_name,
  [342] = 9,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(43), 1,
      sym_identifier,
    ACTIONS(47), 1,
      sym__primitive_type,
    ACTIONS(53), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      sym_comment,
    STATE(15), 1,
      aux_sym_struct_body_repeat1,
    STATE(38), 1,
      sym_struct_field,
    STATE(49), 1,
      sym_type_name,
  [370] = 8,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(58), 1,
      anon_sym_RBRACE,
    ACTIONS(60), 1,
      sym__primitive_type,
    STATE(37), 1,
      sym_message_field,
    STATE(47), 1,
      sym_type_name,
    STATE(14), 2,
      sym_comment,
      aux_sym_message_body_repeat1,
  [396] = 8,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(63), 1,
      sym_identifier,
    ACTIONS(66), 1,
      anon_sym_RBRACE,
    ACTIONS(68), 1,
      sym__primitive_type,
    STATE(38), 1,
      sym_struct_field,
    STATE(49), 1,
      sym_type_name,
    STATE(15), 2,
      sym_comment,
      aux_sym_struct_body_repeat1,
  [422] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    STATE(16), 1,
      sym_comment,
    ACTIONS(71), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [439] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    STATE(17), 1,
      sym_comment,
    ACTIONS(73), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [456] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    STATE(18), 1,
      sym_comment,
    ACTIONS(75), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [473] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    STATE(19), 1,
      sym_comment,
    ACTIONS(77), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [490] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    STATE(20), 1,
      sym_comment,
    ACTIONS(79), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [507] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(21), 1,
      sym_comment,
    ACTIONS(81), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [523] = 7,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(83), 1,
      anon_sym_DQUOTE,
    ACTIONS(85), 1,
      anon_sym_SQUOTE,
    ACTIONS(87), 1,
      aux_sym_path_token1,
    STATE(16), 1,
      sym_path,
    STATE(22), 1,
      sym_comment,
  [545] = 7,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(89), 1,
      sym_identifier,
    ACTIONS(91), 1,
      anon_sym_RBRACE,
    STATE(23), 1,
      sym_comment,
    STATE(29), 1,
      aux_sym_enum_body_repeat1,
    STATE(46), 1,
      sym_enum_field,
  [567] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(24), 1,
      sym_comment,
    ACTIONS(93), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [583] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(25), 1,
      sym_comment,
    ACTIONS(95), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [599] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(26), 1,
      sym_comment,
    ACTIONS(97), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [615] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(27), 1,
      sym_comment,
    ACTIONS(99), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [631] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(28), 1,
      sym_comment,
    ACTIONS(101), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [647] = 6,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(103), 1,
      sym_identifier,
    ACTIONS(106), 1,
      anon_sym_RBRACE,
    STATE(46), 1,
      sym_enum_field,
    STATE(29), 2,
      sym_comment,
      aux_sym_enum_body_repeat1,
  [667] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(30), 1,
      sym_comment,
    ACTIONS(108), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [683] = 7,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(89), 1,
      sym_identifier,
    ACTIONS(110), 1,
      anon_sym_RBRACE,
    STATE(23), 1,
      aux_sym_enum_body_repeat1,
    STATE(31), 1,
      sym_comment,
    STATE(46), 1,
      sym_enum_field,
  [705] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(32), 1,
      sym_comment,
    ACTIONS(112), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [721] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(33), 1,
      sym_comment,
    ACTIONS(114), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [737] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(34), 1,
      sym_comment,
    ACTIONS(116), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [753] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(120), 1,
      sym__primitive_type,
    STATE(35), 1,
      sym_comment,
    ACTIONS(118), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [770] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(124), 1,
      sym__primitive_type,
    STATE(36), 1,
      sym_comment,
    ACTIONS(122), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [787] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(128), 1,
      sym__primitive_type,
    STATE(37), 1,
      sym_comment,
    ACTIONS(126), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [804] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(132), 1,
      sym__primitive_type,
    STATE(38), 1,
      sym_comment,
    ACTIONS(130), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [821] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(136), 1,
      sym__primitive_type,
    STATE(39), 1,
      sym_comment,
    ACTIONS(134), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [838] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(140), 1,
      sym__primitive_type,
    STATE(40), 1,
      sym_comment,
    ACTIONS(138), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [855] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(144), 1,
      sym__primitive_type,
    STATE(41), 1,
      sym_comment,
    ACTIONS(142), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [872] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(148), 1,
      sym__primitive_type,
    STATE(42), 1,
      sym_comment,
    ACTIONS(146), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [889] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(150), 1,
      sym_identifier,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(43), 1,
      sym_comment,
    STATE(51), 1,
      aux_sym__space,
  [905] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(154), 1,
      sym_identifier,
    STATE(44), 1,
      sym_comment,
    STATE(51), 1,
      aux_sym__space,
  [921] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(156), 1,
      sym_identifier,
    STATE(45), 1,
      sym_comment,
    STATE(51), 1,
      aux_sym__space,
  [937] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(46), 1,
      sym_comment,
    ACTIONS(158), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [951] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(160), 1,
      anon_sym_LBRACK_RBRACK,
    STATE(47), 1,
      sym_comment,
    STATE(50), 1,
      aux_sym__space,
  [967] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(162), 1,
      sym_identifier,
    STATE(48), 1,
      sym_comment,
    STATE(51), 1,
      aux_sym__space,
  [983] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(164), 1,
      anon_sym_LBRACK_RBRACK,
    STATE(49), 1,
      sym_comment,
    STATE(58), 1,
      aux_sym__space,
  [999] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(166), 1,
      sym_identifier,
    STATE(50), 1,
      sym_comment,
    STATE(51), 1,
      aux_sym__space,
  [1015] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(168), 1,
      sym_identifier,
    ACTIONS(170), 1,
      aux_sym__space_token1,
    STATE(51), 2,
      sym_comment,
      aux_sym__space,
  [1029] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(173), 1,
      sym_identifier,
    STATE(51), 1,
      aux_sym__space,
    STATE(52), 1,
      sym_comment,
  [1045] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(175), 1,
      anon_sym_LBRACE,
    STATE(28), 1,
      sym_message_body,
    STATE(53), 1,
      sym_comment,
  [1061] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(177), 1,
      anon_sym_LBRACE,
    STATE(33), 1,
      sym_struct_body,
    STATE(54), 1,
      sym_comment,
  [1077] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(179), 1,
      anon_sym_SEMI,
    ACTIONS(181), 1,
      sym_deprecated_tag,
    STATE(55), 1,
      sym_comment,
  [1093] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(56), 1,
      sym_comment,
    ACTIONS(183), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [1107] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(185), 1,
      anon_sym_SEMI,
    ACTIONS(187), 1,
      sym_deprecated_tag,
    STATE(57), 1,
      sym_comment,
  [1123] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(189), 1,
      sym_identifier,
    STATE(51), 1,
      aux_sym__space,
    STATE(58), 1,
      sym_comment,
  [1139] = 5,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    ACTIONS(191), 1,
      sym_identifier,
    STATE(51), 1,
      aux_sym__space,
    STATE(59), 1,
      sym_comment,
  [1155] = 5,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(193), 1,
      anon_sym_LBRACE,
    STATE(25), 1,
      sym_enum_body,
    STATE(60), 1,
      sym_comment,
  [1171] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(52), 1,
      aux_sym__space,
    STATE(61), 1,
      sym_comment,
  [1184] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(195), 1,
      sym__dir,
    STATE(62), 1,
      sym_comment,
  [1197] = 3,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(63), 1,
      sym_comment,
    ACTIONS(197), 2,
      anon_sym_LBRACK_RBRACK,
      aux_sym__space_token1,
  [1208] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(59), 1,
      aux_sym__space,
    STATE(64), 1,
      sym_comment,
  [1221] = 3,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    STATE(65), 1,
      sym_comment,
    ACTIONS(199), 2,
      sym_identifier,
      aux_sym__space_token1,
  [1232] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(201), 1,
      ts_builtin_sym_end,
    STATE(66), 1,
      sym_comment,
  [1245] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(43), 1,
      aux_sym__space,
    STATE(67), 1,
      sym_comment,
  [1258] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(203), 1,
      anon_sym_SEMI,
    STATE(68), 1,
      sym_comment,
  [1271] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(48), 1,
      aux_sym__space,
    STATE(69), 1,
      sym_comment,
  [1284] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(205), 1,
      anon_sym_EQ,
    STATE(70), 1,
      sym_comment,
  [1297] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(207), 1,
      anon_sym_EQ,
    STATE(71), 1,
      sym_comment,
  [1310] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(209), 1,
      anon_sym_SEMI,
    STATE(72), 1,
      sym_comment,
  [1323] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(211), 1,
      aux_sym_comment_token1,
    ACTIONS(213), 1,
      aux_sym__space_token1,
    STATE(73), 1,
      sym_comment,
  [1336] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(215), 1,
      anon_sym_EQ,
    STATE(74), 1,
      sym_comment,
  [1349] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(217), 1,
      sym_number,
    STATE(75), 1,
      sym_comment,
  [1362] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(219), 1,
      anon_sym_SEMI,
    STATE(76), 1,
      sym_comment,
  [1375] = 4,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(221), 1,
      sym__dir,
    STATE(77), 1,
      sym_comment,
  [1388] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(223), 1,
      sym_number,
    STATE(78), 1,
      sym_comment,
  [1401] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(225), 1,
      anon_sym_DQUOTE,
    STATE(79), 1,
      sym_comment,
  [1414] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(227), 1,
      sym_number,
    STATE(80), 1,
      sym_comment,
  [1427] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(225), 1,
      anon_sym_SQUOTE,
    STATE(81), 1,
      sym_comment,
  [1440] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(229), 1,
      anon_sym_SEMI,
    STATE(82), 1,
      sym_comment,
  [1453] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(231), 1,
      anon_sym_SEMI,
    STATE(83), 1,
      sym_comment,
  [1466] = 4,
    ACTIONS(5), 1,
      aux_sym__space_token1,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(233), 1,
      anon_sym_SEMI,
    STATE(84), 1,
      sym_comment,
  [1479] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(45), 1,
      aux_sym__space,
    STATE(85), 1,
      sym_comment,
  [1492] = 4,
    ACTIONS(23), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      aux_sym__space_token1,
    STATE(44), 1,
      aux_sym__space,
    STATE(86), 1,
      sym_comment,
  [1505] = 1,
    ACTIONS(235), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 39,
  [SMALL_STATE(4)] = 78,
  [SMALL_STATE(5)] = 117,
  [SMALL_STATE(6)] = 147,
  [SMALL_STATE(7)] = 177,
  [SMALL_STATE(8)] = 207,
  [SMALL_STATE(9)] = 235,
  [SMALL_STATE(10)] = 258,
  [SMALL_STATE(11)] = 286,
  [SMALL_STATE(12)] = 314,
  [SMALL_STATE(13)] = 342,
  [SMALL_STATE(14)] = 370,
  [SMALL_STATE(15)] = 396,
  [SMALL_STATE(16)] = 422,
  [SMALL_STATE(17)] = 439,
  [SMALL_STATE(18)] = 456,
  [SMALL_STATE(19)] = 473,
  [SMALL_STATE(20)] = 490,
  [SMALL_STATE(21)] = 507,
  [SMALL_STATE(22)] = 523,
  [SMALL_STATE(23)] = 545,
  [SMALL_STATE(24)] = 567,
  [SMALL_STATE(25)] = 583,
  [SMALL_STATE(26)] = 599,
  [SMALL_STATE(27)] = 615,
  [SMALL_STATE(28)] = 631,
  [SMALL_STATE(29)] = 647,
  [SMALL_STATE(30)] = 667,
  [SMALL_STATE(31)] = 683,
  [SMALL_STATE(32)] = 705,
  [SMALL_STATE(33)] = 721,
  [SMALL_STATE(34)] = 737,
  [SMALL_STATE(35)] = 753,
  [SMALL_STATE(36)] = 770,
  [SMALL_STATE(37)] = 787,
  [SMALL_STATE(38)] = 804,
  [SMALL_STATE(39)] = 821,
  [SMALL_STATE(40)] = 838,
  [SMALL_STATE(41)] = 855,
  [SMALL_STATE(42)] = 872,
  [SMALL_STATE(43)] = 889,
  [SMALL_STATE(44)] = 905,
  [SMALL_STATE(45)] = 921,
  [SMALL_STATE(46)] = 937,
  [SMALL_STATE(47)] = 951,
  [SMALL_STATE(48)] = 967,
  [SMALL_STATE(49)] = 983,
  [SMALL_STATE(50)] = 999,
  [SMALL_STATE(51)] = 1015,
  [SMALL_STATE(52)] = 1029,
  [SMALL_STATE(53)] = 1045,
  [SMALL_STATE(54)] = 1061,
  [SMALL_STATE(55)] = 1077,
  [SMALL_STATE(56)] = 1093,
  [SMALL_STATE(57)] = 1107,
  [SMALL_STATE(58)] = 1123,
  [SMALL_STATE(59)] = 1139,
  [SMALL_STATE(60)] = 1155,
  [SMALL_STATE(61)] = 1171,
  [SMALL_STATE(62)] = 1184,
  [SMALL_STATE(63)] = 1197,
  [SMALL_STATE(64)] = 1208,
  [SMALL_STATE(65)] = 1221,
  [SMALL_STATE(66)] = 1232,
  [SMALL_STATE(67)] = 1245,
  [SMALL_STATE(68)] = 1258,
  [SMALL_STATE(69)] = 1271,
  [SMALL_STATE(70)] = 1284,
  [SMALL_STATE(71)] = 1297,
  [SMALL_STATE(72)] = 1310,
  [SMALL_STATE(73)] = 1323,
  [SMALL_STATE(74)] = 1336,
  [SMALL_STATE(75)] = 1349,
  [SMALL_STATE(76)] = 1362,
  [SMALL_STATE(77)] = 1375,
  [SMALL_STATE(78)] = 1388,
  [SMALL_STATE(79)] = 1401,
  [SMALL_STATE(80)] = 1414,
  [SMALL_STATE(81)] = 1427,
  [SMALL_STATE(82)] = 1440,
  [SMALL_STATE(83)] = 1453,
  [SMALL_STATE(84)] = 1466,
  [SMALL_STATE(85)] = 1479,
  [SMALL_STATE(86)] = 1492,
  [SMALL_STATE(87)] = 1505,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [7] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 3, 0, 0),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(85),
  [32] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(67),
  [35] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(69),
  [38] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(22),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [47] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0),
  [60] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [63] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_include_directive, 2, 0, 0),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [77] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 3, 0, 0),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package_declaration, 4, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 3, 0, 0),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [85] = {.entry = {.count = 1, .reusable = false}}, SHIFT(62),
  [87] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [93] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 2, 0, 0),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_declaration, 4, 0, 0),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_body, 2, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 1, 0, 0),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_declaration, 4, 0, 0),
  [103] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(71),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 3, 0, 0),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_body, 3, 0, 0),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_declaration, 4, 0, 0),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 2, 0, 0),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_field, 4, 0, 2),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_struct_field, 4, 0, 2),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 8, 0, 5),
  [124] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 8, 0, 5),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 1, 0, 0),
  [128] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 1, 0, 0),
  [130] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 1, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_struct_body_repeat1, 1, 0, 0),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 7, 0, 4),
  [136] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 7, 0, 4),
  [138] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 6, 0, 4),
  [140] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 6, 0, 4),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 7, 0, 5),
  [144] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 7, 0, 5),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_field, 5, 0, 3),
  [148] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_struct_field, 5, 0, 3),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 1, 0, 0),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__space, 2, 0, 0),
  [170] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__space, 2, 0, 0), SHIFT_REPEAT(65),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [177] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field, 4, 0, 1),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [195] = {.entry = {.count = 1, .reusable = false}}, SHIFT(81),
  [197] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 1, 0, 0),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__space, 1, 0, 0),
  [201] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [205] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(80),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [211] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [213] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [215] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [219] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [221] = {.entry = {.count = 1, .reusable = false}}, SHIFT(79),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [233] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2, 0, 0),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_kiwi(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
