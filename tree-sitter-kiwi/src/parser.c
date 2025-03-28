#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 99
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 52
#define ALIAS_COUNT 0
#define TOKEN_COUNT 32
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 5
#define MAX_ALIAS_SEQUENCE_LENGTH 8
#define PRODUCTION_ID_COUNT 4

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SLASH_SLASH_SLASH_ATinclude = 2,
  anon_sym_DQUOTE = 3,
  anon_sym_SQUOTE = 4,
  aux_sym_path_token1 = 5,
  anon_sym_SLASH_SLASH = 6,
  aux_sym_comment_token1 = 7,
  anon_sym_package = 8,
  anon_sym_SEMI = 9,
  anon_sym_enum = 10,
  anon_sym_LBRACE = 11,
  anon_sym_RBRACE = 12,
  anon_sym_EQ = 13,
  anon_sym_message = 14,
  anon_sym_LBRACK_RBRACK = 15,
  anon_sym_bool = 16,
  anon_sym_byte = 17,
  anon_sym_int32 = 18,
  anon_sym_int64 = 19,
  anon_sym_uint32 = 20,
  anon_sym_uint64 = 21,
  anon_sym_float = 22,
  anon_sym_double = 23,
  anon_sym_string = 24,
  anon_sym_LBRACKdeprecated_RBRACK = 25,
  anon_sym_LBRACKdeprecated_LPAREN = 26,
  aux_sym_deprecated_tag_token1 = 27,
  anon_sym_RPAREN_RBRACK = 28,
  sym_number = 29,
  sym_dir = 30,
  aux_sym_space_token1 = 31,
  sym_source_file = 32,
  sym_include_directive = 33,
  sym_path = 34,
  sym_comment = 35,
  sym_package_declaration = 36,
  sym_enum_definition = 37,
  sym_enum_body = 38,
  sym_enum_field = 39,
  sym_message_definition = 40,
  sym_message_body = 41,
  sym_message_field = 42,
  sym_type_name = 43,
  sym_deprecated_tag = 44,
  sym_space = 45,
  aux_sym_source_file_repeat1 = 46,
  aux_sym_source_file_repeat2 = 47,
  aux_sym_source_file_repeat3 = 48,
  aux_sym_enum_body_repeat1 = 49,
  aux_sym_message_body_repeat1 = 50,
  aux_sym_space_repeat1 = 51,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SLASH_SLASH_SLASH_ATinclude] = "/// @include ",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_path_token1] = "path_token1",
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
  [anon_sym_bool] = "bool",
  [anon_sym_byte] = "byte",
  [anon_sym_int32] = "int32",
  [anon_sym_int64] = "int64",
  [anon_sym_uint32] = "uint32",
  [anon_sym_uint64] = "uint64",
  [anon_sym_float] = "float",
  [anon_sym_double] = "double",
  [anon_sym_string] = "string",
  [anon_sym_LBRACKdeprecated_RBRACK] = "[deprecated]",
  [anon_sym_LBRACKdeprecated_LPAREN] = "[deprecated(",
  [aux_sym_deprecated_tag_token1] = "deprecated_tag_token1",
  [anon_sym_RPAREN_RBRACK] = ")]",
  [sym_number] = "number",
  [sym_dir] = "dir",
  [aux_sym_space_token1] = "space_token1",
  [sym_source_file] = "source_file",
  [sym_include_directive] = "include_directive",
  [sym_path] = "path",
  [sym_comment] = "comment",
  [sym_package_declaration] = "package_declaration",
  [sym_enum_definition] = "enum_definition",
  [sym_enum_body] = "enum_body",
  [sym_enum_field] = "enum_field",
  [sym_message_definition] = "message_definition",
  [sym_message_body] = "message_body",
  [sym_message_field] = "message_field",
  [sym_type_name] = "type_name",
  [sym_deprecated_tag] = "deprecated_tag",
  [sym_space] = "space",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_source_file_repeat2] = "source_file_repeat2",
  [aux_sym_source_file_repeat3] = "source_file_repeat3",
  [aux_sym_enum_body_repeat1] = "enum_body_repeat1",
  [aux_sym_message_body_repeat1] = "message_body_repeat1",
  [aux_sym_space_repeat1] = "space_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SLASH_SLASH_SLASH_ATinclude] = anon_sym_SLASH_SLASH_SLASH_ATinclude,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_path_token1] = aux_sym_path_token1,
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
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_byte] = anon_sym_byte,
  [anon_sym_int32] = anon_sym_int32,
  [anon_sym_int64] = anon_sym_int64,
  [anon_sym_uint32] = anon_sym_uint32,
  [anon_sym_uint64] = anon_sym_uint64,
  [anon_sym_float] = anon_sym_float,
  [anon_sym_double] = anon_sym_double,
  [anon_sym_string] = anon_sym_string,
  [anon_sym_LBRACKdeprecated_RBRACK] = anon_sym_LBRACKdeprecated_RBRACK,
  [anon_sym_LBRACKdeprecated_LPAREN] = anon_sym_LBRACKdeprecated_LPAREN,
  [aux_sym_deprecated_tag_token1] = aux_sym_deprecated_tag_token1,
  [anon_sym_RPAREN_RBRACK] = anon_sym_RPAREN_RBRACK,
  [sym_number] = sym_number,
  [sym_dir] = sym_dir,
  [aux_sym_space_token1] = aux_sym_space_token1,
  [sym_source_file] = sym_source_file,
  [sym_include_directive] = sym_include_directive,
  [sym_path] = sym_path,
  [sym_comment] = sym_comment,
  [sym_package_declaration] = sym_package_declaration,
  [sym_enum_definition] = sym_enum_definition,
  [sym_enum_body] = sym_enum_body,
  [sym_enum_field] = sym_enum_field,
  [sym_message_definition] = sym_message_definition,
  [sym_message_body] = sym_message_body,
  [sym_message_field] = sym_message_field,
  [sym_type_name] = sym_type_name,
  [sym_deprecated_tag] = sym_deprecated_tag,
  [sym_space] = sym_space,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_source_file_repeat2] = aux_sym_source_file_repeat2,
  [aux_sym_source_file_repeat3] = aux_sym_source_file_repeat3,
  [aux_sym_enum_body_repeat1] = aux_sym_enum_body_repeat1,
  [aux_sym_message_body_repeat1] = aux_sym_message_body_repeat1,
  [aux_sym_space_repeat1] = aux_sym_space_repeat1,
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
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_byte] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_int64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint32] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_uint64] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_float] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_double] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_string] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACKdeprecated_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACKdeprecated_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_deprecated_tag_token1] = {
    .visible = false,
    .named = false,
  },
  [anon_sym_RPAREN_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_dir] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_space_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_include_directive] = {
    .visible = true,
    .named = true,
  },
  [sym_path] = {
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
  [sym_enum_definition] = {
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
  [sym_message_definition] = {
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
  [sym_type_name] = {
    .visible = true,
    .named = true,
  },
  [sym_deprecated_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_space] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat3] = {
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
  [aux_sym_space_repeat1] = {
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
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_enum_field_name] = "enum_field_name",
  [field_enum_field_value] = "enum_field_value",
  [field_message_field_name] = "message_field_name",
  [field_message_field_type] = "message_field_type",
  [field_message_field_value] = "message_field_value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 2},
  [2] = {.index = 2, .length = 3},
  [3] = {.index = 5, .length = 4},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_enum_field_name, 0},
    {field_enum_field_value, 2},
  [2] =
    {field_message_field_name, 2},
    {field_message_field_type, 0},
    {field_message_field_value, 4},
  [5] =
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
  [31] = 26,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 26,
  [36] = 5,
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
  [55] = 26,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 5,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 5,
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
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 94,
  [95] = 95,
  [96] = 91,
  [97] = 91,
  [98] = 91,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(29);
      ADVANCE_MAP(
        '"', 31,
        '\'', 33,
        ')', 8,
        '/', 5,
        ';', 40,
        '=', 43,
        '[', 9,
        '{', 41,
        '}', 42,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(52);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(49);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(7);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(30);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(32);
      if (lookahead == '\'') ADVANCE(34);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(52);
      if (lookahead != 0) ADVANCE(35);
      END_STATE();
    case 4:
      if (lookahead == '(') ADVANCE(46);
      if (lookahead == ']') ADVANCE(45);
      END_STATE();
    case 5:
      if (lookahead == '/') ADVANCE(37);
      END_STATE();
    case 6:
      if (lookahead == '/') ADVANCE(36);
      END_STATE();
    case 7:
      if (lookahead == '@') ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == ']') ADVANCE(48);
      END_STATE();
    case 9:
      if (lookahead == ']') ADVANCE(44);
      if (lookahead == 'd') ADVANCE(15);
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
      if (lookahead == 'd') ADVANCE(4);
      END_STATE();
    case 14:
      if (lookahead == 'd') ADVANCE(17);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(11);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(2);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(13);
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
      if (lookahead == 't') ADVANCE(18);
      END_STATE();
    case 25:
      if (lookahead == 'u') ADVANCE(14);
      END_STATE();
    case 26:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(52);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(51);
      END_STATE();
    case 27:
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(47);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(47);
      END_STATE();
    case 28:
      if (eof) ADVANCE(29);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == '{') ADVANCE(41);
      if (lookahead == '}') ADVANCE(42);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(52);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(49);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH_ATinclude);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(35);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(35);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(aux_sym_path_token1);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(35);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(1);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '\n') ADVANCE(52);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(39);
      if (lookahead != 0) ADVANCE(39);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(39);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_LBRACK_RBRACK);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_LBRACKdeprecated_RBRACK);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_LBRACKdeprecated_LPAREN);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_deprecated_tag_token1);
      if (lookahead != 0 &&
          lookahead != ')') ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_RPAREN_RBRACK);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(49);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_dir);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(51);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_space_token1);
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
      ADVANCE_MAP(
        'b', 1,
        'd', 2,
        'e', 3,
        'f', 4,
        'i', 5,
        'm', 6,
        'p', 7,
        's', 8,
        'u', 9,
      );
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(10);
      if (lookahead == 'y') ADVANCE(11);
      END_STATE();
    case 2:
      if (lookahead == 'o') ADVANCE(12);
      END_STATE();
    case 3:
      if (lookahead == 'n') ADVANCE(13);
      END_STATE();
    case 4:
      if (lookahead == 'l') ADVANCE(14);
      END_STATE();
    case 5:
      if (lookahead == 'n') ADVANCE(15);
      END_STATE();
    case 6:
      if (lookahead == 'e') ADVANCE(16);
      END_STATE();
    case 7:
      if (lookahead == 'a') ADVANCE(17);
      END_STATE();
    case 8:
      if (lookahead == 't') ADVANCE(18);
      END_STATE();
    case 9:
      if (lookahead == 'i') ADVANCE(19);
      END_STATE();
    case 10:
      if (lookahead == 'o') ADVANCE(20);
      END_STATE();
    case 11:
      if (lookahead == 't') ADVANCE(21);
      END_STATE();
    case 12:
      if (lookahead == 'u') ADVANCE(22);
      END_STATE();
    case 13:
      if (lookahead == 'u') ADVANCE(23);
      END_STATE();
    case 14:
      if (lookahead == 'o') ADVANCE(24);
      END_STATE();
    case 15:
      if (lookahead == 't') ADVANCE(25);
      END_STATE();
    case 16:
      if (lookahead == 's') ADVANCE(26);
      END_STATE();
    case 17:
      if (lookahead == 'c') ADVANCE(27);
      END_STATE();
    case 18:
      if (lookahead == 'r') ADVANCE(28);
      END_STATE();
    case 19:
      if (lookahead == 'n') ADVANCE(29);
      END_STATE();
    case 20:
      if (lookahead == 'l') ADVANCE(30);
      END_STATE();
    case 21:
      if (lookahead == 'e') ADVANCE(31);
      END_STATE();
    case 22:
      if (lookahead == 'b') ADVANCE(32);
      END_STATE();
    case 23:
      if (lookahead == 'm') ADVANCE(33);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(34);
      END_STATE();
    case 25:
      if (lookahead == '3') ADVANCE(35);
      if (lookahead == '6') ADVANCE(36);
      END_STATE();
    case 26:
      if (lookahead == 's') ADVANCE(37);
      END_STATE();
    case 27:
      if (lookahead == 'k') ADVANCE(38);
      END_STATE();
    case 28:
      if (lookahead == 'i') ADVANCE(39);
      END_STATE();
    case 29:
      if (lookahead == 't') ADVANCE(40);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_byte);
      END_STATE();
    case 32:
      if (lookahead == 'l') ADVANCE(41);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_enum);
      END_STATE();
    case 34:
      if (lookahead == 't') ADVANCE(42);
      END_STATE();
    case 35:
      if (lookahead == '2') ADVANCE(43);
      END_STATE();
    case 36:
      if (lookahead == '4') ADVANCE(44);
      END_STATE();
    case 37:
      if (lookahead == 'a') ADVANCE(45);
      END_STATE();
    case 38:
      if (lookahead == 'a') ADVANCE(46);
      END_STATE();
    case 39:
      if (lookahead == 'n') ADVANCE(47);
      END_STATE();
    case 40:
      if (lookahead == '3') ADVANCE(48);
      if (lookahead == '6') ADVANCE(49);
      END_STATE();
    case 41:
      if (lookahead == 'e') ADVANCE(50);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_float);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_int32);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_int64);
      END_STATE();
    case 45:
      if (lookahead == 'g') ADVANCE(51);
      END_STATE();
    case 46:
      if (lookahead == 'g') ADVANCE(52);
      END_STATE();
    case 47:
      if (lookahead == 'g') ADVANCE(53);
      END_STATE();
    case 48:
      if (lookahead == '2') ADVANCE(54);
      END_STATE();
    case 49:
      if (lookahead == '4') ADVANCE(55);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_double);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(56);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(57);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_string);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_uint32);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(anon_sym_uint64);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(anon_sym_message);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(anon_sym_package);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 28},
  [3] = {.lex_state = 28},
  [4] = {.lex_state = 28},
  [5] = {.lex_state = 28},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 28},
  [13] = {.lex_state = 28},
  [14] = {.lex_state = 28},
  [15] = {.lex_state = 28},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 28},
  [20] = {.lex_state = 28},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 28},
  [23] = {.lex_state = 28},
  [24] = {.lex_state = 28},
  [25] = {.lex_state = 28},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 28},
  [28] = {.lex_state = 28},
  [29] = {.lex_state = 28},
  [30] = {.lex_state = 28},
  [31] = {.lex_state = 28},
  [32] = {.lex_state = 28},
  [33] = {.lex_state = 28},
  [34] = {.lex_state = 28},
  [35] = {.lex_state = 28},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 28},
  [42] = {.lex_state = 28},
  [43] = {.lex_state = 28},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 28},
  [47] = {.lex_state = 28},
  [48] = {.lex_state = 3},
  [49] = {.lex_state = 28},
  [50] = {.lex_state = 28},
  [51] = {.lex_state = 28},
  [52] = {.lex_state = 28},
  [53] = {.lex_state = 28},
  [54] = {.lex_state = 28},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 28},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 28},
  [60] = {.lex_state = 28},
  [61] = {.lex_state = 28},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 26},
  [71] = {.lex_state = 0},
  [72] = {.lex_state = 0},
  [73] = {.lex_state = 0},
  [74] = {.lex_state = 0},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 0},
  [78] = {.lex_state = 0},
  [79] = {.lex_state = 0},
  [80] = {.lex_state = 0},
  [81] = {.lex_state = 0},
  [82] = {.lex_state = 27},
  [83] = {.lex_state = 0},
  [84] = {.lex_state = 26},
  [85] = {.lex_state = 0},
  [86] = {.lex_state = 0},
  [87] = {.lex_state = 0},
  [88] = {.lex_state = 0},
  [89] = {.lex_state = 0},
  [90] = {.lex_state = 0},
  [91] = {.lex_state = 38},
  [92] = {.lex_state = 0},
  [93] = {.lex_state = 0},
  [94] = {.lex_state = 0},
  [95] = {.lex_state = 0},
  [96] = {.lex_state = 38},
  [97] = {.lex_state = 38},
  [98] = {.lex_state = 38},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SLASH_SLASH_SLASH_ATinclude] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [anon_sym_SLASH_SLASH] = ACTIONS(1),
    [anon_sym_package] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_message] = ACTIONS(1),
    [anon_sym_LBRACK_RBRACK] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_byte] = ACTIONS(1),
    [anon_sym_int32] = ACTIONS(1),
    [anon_sym_int64] = ACTIONS(1),
    [anon_sym_uint32] = ACTIONS(1),
    [anon_sym_uint64] = ACTIONS(1),
    [anon_sym_float] = ACTIONS(1),
    [anon_sym_double] = ACTIONS(1),
    [anon_sym_string] = ACTIONS(1),
    [anon_sym_LBRACKdeprecated_RBRACK] = ACTIONS(1),
    [anon_sym_LBRACKdeprecated_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN_RBRACK] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [aux_sym_space_token1] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(78),
    [sym_include_directive] = STATE(8),
    [sym_comment] = STATE(10),
    [sym_package_declaration] = STATE(11),
    [sym_enum_definition] = STATE(24),
    [sym_message_definition] = STATE(24),
    [aux_sym_source_file_repeat1] = STATE(10),
    [aux_sym_source_file_repeat2] = STATE(8),
    [aux_sym_source_file_repeat3] = STATE(24),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_SLASH_SLASH_SLASH_ATinclude] = ACTIONS(7),
    [anon_sym_SLASH_SLASH] = ACTIONS(9),
    [anon_sym_package] = ACTIONS(11),
    [anon_sym_enum] = ACTIONS(13),
    [anon_sym_message] = ACTIONS(15),
    [aux_sym_space_token1] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(21), 1,
      anon_sym_RBRACE,
    STATE(62), 1,
      sym_type_name,
    STATE(4), 3,
      sym_comment,
      sym_message_field,
      aux_sym_message_body_repeat1,
    ACTIONS(17), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [30] = 6,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(23), 1,
      anon_sym_RBRACE,
    STATE(62), 1,
      sym_type_name,
    STATE(2), 3,
      sym_comment,
      sym_message_field,
      aux_sym_message_body_repeat1,
    ACTIONS(17), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [60] = 6,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(28), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(31), 1,
      anon_sym_RBRACE,
    STATE(62), 1,
      sym_type_name,
    STATE(4), 3,
      sym_comment,
      sym_message_field,
      aux_sym_message_body_repeat1,
    ACTIONS(25), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [90] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(35), 3,
      anon_sym_SLASH_SLASH,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
    ACTIONS(33), 12,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [113] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    STATE(9), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(17), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(20), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [145] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    STATE(17), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(21), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(20), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [177] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    STATE(18), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(21), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(19), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [209] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(41), 1,
      ts_builtin_sym_end,
    STATE(16), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(21), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(23), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [241] = 11,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(11), 1,
      anon_sym_package,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    STATE(6), 1,
      sym_package_declaration,
    STATE(37), 1,
      sym_include_directive,
    STATE(26), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [277] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    STATE(7), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(18), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(19), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [309] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(45), 2,
      anon_sym_SLASH_SLASH,
      anon_sym_RBRACE,
    ACTIONS(43), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [329] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(49), 2,
      anon_sym_SLASH_SLASH,
      anon_sym_RBRACE,
    ACTIONS(47), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [349] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(53), 2,
      anon_sym_SLASH_SLASH,
      anon_sym_RBRACE,
    ACTIONS(51), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [369] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(57), 2,
      anon_sym_SLASH_SLASH,
      anon_sym_RBRACE,
    ACTIONS(55), 10,
      anon_sym_bool,
      anon_sym_byte,
      anon_sym_int32,
      anon_sym_int64,
      anon_sym_uint32,
      anon_sym_uint64,
      anon_sym_float,
      anon_sym_double,
      anon_sym_string,
      sym_identifier,
  [389] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    STATE(37), 1,
      sym_include_directive,
    STATE(26), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [419] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(41), 1,
      ts_builtin_sym_end,
    STATE(37), 1,
      sym_include_directive,
    STATE(26), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [449] = 9,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(9), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    STATE(37), 1,
      sym_include_directive,
    STATE(26), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [479] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(27), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(22), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [504] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(41), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(28), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(22), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [529] = 6,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(65), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(68), 1,
      anon_sym_SLASH_SLASH,
    STATE(21), 2,
      sym_include_directive,
      aux_sym_source_file_repeat2,
    STATE(39), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(63), 3,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
  [552] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(71), 1,
      ts_builtin_sym_end,
    ACTIONS(73), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(76), 1,
      anon_sym_enum,
    ACTIONS(79), 1,
      anon_sym_message,
    STATE(30), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(22), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [577] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(29), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(22), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [602] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(39), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(25), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(22), 3,
      sym_enum_definition,
      sym_message_definition,
      aux_sym_source_file_repeat3,
  [627] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(35), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [651] = 4,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(84), 1,
      anon_sym_SLASH_SLASH,
    STATE(26), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(82), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_package,
      anon_sym_enum,
      anon_sym_message,
  [669] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(41), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(35), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [693] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(59), 1,
      ts_builtin_sym_end,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    STATE(35), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [717] = 7,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(61), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(87), 1,
      ts_builtin_sym_end,
    STATE(35), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [741] = 6,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(13), 1,
      anon_sym_enum,
    ACTIONS(15), 1,
      anon_sym_message,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    STATE(31), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    STATE(47), 2,
      sym_enum_definition,
      sym_message_definition,
  [762] = 4,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(89), 1,
      anon_sym_SLASH_SLASH,
    STATE(31), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(82), 3,
      anon_sym_enum,
      anon_sym_LBRACE,
      anon_sym_message,
  [778] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(92), 1,
      sym_identifier,
    ACTIONS(94), 1,
      anon_sym_RBRACE,
    STATE(33), 3,
      sym_comment,
      sym_enum_field,
      aux_sym_enum_body_repeat1,
  [796] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(96), 1,
      sym_identifier,
    ACTIONS(99), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(102), 1,
      anon_sym_RBRACE,
    STATE(33), 3,
      sym_comment,
      sym_enum_field,
      aux_sym_enum_body_repeat1,
  [814] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(92), 1,
      sym_identifier,
    ACTIONS(104), 1,
      anon_sym_RBRACE,
    STATE(32), 3,
      sym_comment,
      sym_enum_field,
      aux_sym_enum_body_repeat1,
  [832] = 4,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(106), 1,
      anon_sym_SLASH_SLASH,
    STATE(35), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(82), 3,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
  [848] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(33), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(35), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_package,
      anon_sym_enum,
      anon_sym_message,
  [862] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(109), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(63), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
  [875] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(113), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(111), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
  [888] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(115), 1,
      anon_sym_SLASH_SLASH,
    STATE(37), 1,
      sym_include_directive,
    STATE(55), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [905] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(119), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(117), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
  [918] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(121), 1,
      anon_sym_LBRACE,
    STATE(52), 1,
      sym_enum_body,
    STATE(31), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [935] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(123), 1,
      anon_sym_LBRACE,
    STATE(56), 1,
      sym_message_body,
    STATE(31), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [952] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(121), 1,
      anon_sym_LBRACE,
    STATE(50), 1,
      sym_enum_body,
    STATE(41), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [969] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(127), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(125), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
  [982] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(131), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(129), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
  [995] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(19), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(123), 1,
      anon_sym_LBRACE,
    STATE(49), 1,
      sym_message_body,
    STATE(42), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [1012] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(71), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1022] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(133), 1,
      anon_sym_DQUOTE,
    ACTIONS(135), 1,
      anon_sym_SQUOTE,
    ACTIONS(137), 1,
      aux_sym_path_token1,
    STATE(45), 1,
      sym_path,
  [1038] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(139), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1048] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(141), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1058] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(143), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1068] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(145), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1078] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(147), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1088] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(149), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1098] = 4,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(82), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(151), 1,
      anon_sym_SLASH_SLASH,
    STATE(55), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
  [1112] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(154), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1122] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(156), 1,
      anon_sym_SEMI,
    ACTIONS(158), 1,
      anon_sym_LBRACKdeprecated_RBRACK,
    ACTIONS(160), 1,
      anon_sym_LBRACKdeprecated_LPAREN,
    STATE(85), 1,
      sym_deprecated_tag,
  [1138] = 5,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(158), 1,
      anon_sym_LBRACKdeprecated_RBRACK,
    ACTIONS(160), 1,
      anon_sym_LBRACKdeprecated_LPAREN,
    ACTIONS(162), 1,
      anon_sym_SEMI,
    STATE(83), 1,
      sym_deprecated_tag,
  [1154] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(164), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1164] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(35), 4,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH,
      anon_sym_enum,
      anon_sym_message,
  [1174] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(166), 3,
      anon_sym_SLASH_SLASH,
      anon_sym_RBRACE,
      sym_identifier,
  [1183] = 4,
    ACTIONS(168), 1,
      anon_sym_LBRACK_RBRACK,
    ACTIONS(170), 1,
      aux_sym_space_token1,
    STATE(65), 1,
      aux_sym_space_repeat1,
    STATE(79), 1,
      sym_space,
  [1196] = 3,
    ACTIONS(172), 1,
      sym_identifier,
    ACTIONS(174), 1,
      aux_sym_space_token1,
    STATE(63), 1,
      aux_sym_space_repeat1,
  [1206] = 3,
    ACTIONS(170), 1,
      aux_sym_space_token1,
    STATE(65), 1,
      aux_sym_space_repeat1,
    STATE(90), 1,
      sym_space,
  [1216] = 3,
    ACTIONS(177), 1,
      sym_identifier,
    ACTIONS(179), 1,
      aux_sym_space_token1,
    STATE(63), 1,
      aux_sym_space_repeat1,
  [1226] = 3,
    ACTIONS(170), 1,
      aux_sym_space_token1,
    STATE(65), 1,
      aux_sym_space_repeat1,
    STATE(72), 1,
      sym_space,
  [1236] = 3,
    ACTIONS(170), 1,
      aux_sym_space_token1,
    STATE(65), 1,
      aux_sym_space_repeat1,
    STATE(80), 1,
      sym_space,
  [1246] = 3,
    ACTIONS(170), 1,
      aux_sym_space_token1,
    STATE(65), 1,
      aux_sym_space_repeat1,
    STATE(88), 1,
      sym_space,
  [1256] = 3,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(33), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(35), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
  [1266] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(181), 1,
      sym_dir,
  [1273] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(183), 1,
      anon_sym_DQUOTE,
  [1280] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(185), 1,
      sym_identifier,
  [1287] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(187), 1,
      anon_sym_EQ,
  [1294] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(183), 1,
      anon_sym_SQUOTE,
  [1301] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(189), 1,
      anon_sym_EQ,
  [1308] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(191), 1,
      sym_number,
  [1315] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(193), 1,
      sym_number,
  [1322] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(195), 1,
      ts_builtin_sym_end,
  [1329] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(197), 1,
      sym_identifier,
  [1336] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(199), 1,
      sym_identifier,
  [1343] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(201), 1,
      anon_sym_SEMI,
  [1350] = 2,
    ACTIONS(203), 1,
      aux_sym_deprecated_tag_token1,
    ACTIONS(205), 1,
      aux_sym_space_token1,
  [1357] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(207), 1,
      anon_sym_SEMI,
  [1364] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(209), 1,
      sym_dir,
  [1371] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(211), 1,
      anon_sym_SEMI,
  [1378] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(213), 1,
      anon_sym_RPAREN_RBRACK,
  [1385] = 1,
    ACTIONS(215), 2,
      anon_sym_LBRACK_RBRACK,
      aux_sym_space_token1,
  [1390] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(217), 1,
      sym_identifier,
  [1397] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(219), 1,
      anon_sym_SEMI,
  [1404] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(221), 1,
      sym_identifier,
  [1411] = 2,
    ACTIONS(205), 1,
      aux_sym_space_token1,
    ACTIONS(223), 1,
      aux_sym_comment_token1,
  [1418] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(225), 1,
      anon_sym_EQ,
  [1425] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(227), 1,
      anon_sym_SEMI,
  [1432] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(229), 1,
      anon_sym_SEMI,
  [1439] = 2,
    ACTIONS(3), 1,
      aux_sym_space_token1,
    ACTIONS(231), 1,
      sym_number,
  [1446] = 2,
    ACTIONS(205), 1,
      aux_sym_space_token1,
    ACTIONS(233), 1,
      aux_sym_comment_token1,
  [1453] = 2,
    ACTIONS(205), 1,
      aux_sym_space_token1,
    ACTIONS(235), 1,
      aux_sym_comment_token1,
  [1460] = 2,
    ACTIONS(205), 1,
      aux_sym_space_token1,
    ACTIONS(237), 1,
      aux_sym_comment_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 30,
  [SMALL_STATE(4)] = 60,
  [SMALL_STATE(5)] = 90,
  [SMALL_STATE(6)] = 113,
  [SMALL_STATE(7)] = 145,
  [SMALL_STATE(8)] = 177,
  [SMALL_STATE(9)] = 209,
  [SMALL_STATE(10)] = 241,
  [SMALL_STATE(11)] = 277,
  [SMALL_STATE(12)] = 309,
  [SMALL_STATE(13)] = 329,
  [SMALL_STATE(14)] = 349,
  [SMALL_STATE(15)] = 369,
  [SMALL_STATE(16)] = 389,
  [SMALL_STATE(17)] = 419,
  [SMALL_STATE(18)] = 449,
  [SMALL_STATE(19)] = 479,
  [SMALL_STATE(20)] = 504,
  [SMALL_STATE(21)] = 529,
  [SMALL_STATE(22)] = 552,
  [SMALL_STATE(23)] = 577,
  [SMALL_STATE(24)] = 602,
  [SMALL_STATE(25)] = 627,
  [SMALL_STATE(26)] = 651,
  [SMALL_STATE(27)] = 669,
  [SMALL_STATE(28)] = 693,
  [SMALL_STATE(29)] = 717,
  [SMALL_STATE(30)] = 741,
  [SMALL_STATE(31)] = 762,
  [SMALL_STATE(32)] = 778,
  [SMALL_STATE(33)] = 796,
  [SMALL_STATE(34)] = 814,
  [SMALL_STATE(35)] = 832,
  [SMALL_STATE(36)] = 848,
  [SMALL_STATE(37)] = 862,
  [SMALL_STATE(38)] = 875,
  [SMALL_STATE(39)] = 888,
  [SMALL_STATE(40)] = 905,
  [SMALL_STATE(41)] = 918,
  [SMALL_STATE(42)] = 935,
  [SMALL_STATE(43)] = 952,
  [SMALL_STATE(44)] = 969,
  [SMALL_STATE(45)] = 982,
  [SMALL_STATE(46)] = 995,
  [SMALL_STATE(47)] = 1012,
  [SMALL_STATE(48)] = 1022,
  [SMALL_STATE(49)] = 1038,
  [SMALL_STATE(50)] = 1048,
  [SMALL_STATE(51)] = 1058,
  [SMALL_STATE(52)] = 1068,
  [SMALL_STATE(53)] = 1078,
  [SMALL_STATE(54)] = 1088,
  [SMALL_STATE(55)] = 1098,
  [SMALL_STATE(56)] = 1112,
  [SMALL_STATE(57)] = 1122,
  [SMALL_STATE(58)] = 1138,
  [SMALL_STATE(59)] = 1154,
  [SMALL_STATE(60)] = 1164,
  [SMALL_STATE(61)] = 1174,
  [SMALL_STATE(62)] = 1183,
  [SMALL_STATE(63)] = 1196,
  [SMALL_STATE(64)] = 1206,
  [SMALL_STATE(65)] = 1216,
  [SMALL_STATE(66)] = 1226,
  [SMALL_STATE(67)] = 1236,
  [SMALL_STATE(68)] = 1246,
  [SMALL_STATE(69)] = 1256,
  [SMALL_STATE(70)] = 1266,
  [SMALL_STATE(71)] = 1273,
  [SMALL_STATE(72)] = 1280,
  [SMALL_STATE(73)] = 1287,
  [SMALL_STATE(74)] = 1294,
  [SMALL_STATE(75)] = 1301,
  [SMALL_STATE(76)] = 1308,
  [SMALL_STATE(77)] = 1315,
  [SMALL_STATE(78)] = 1322,
  [SMALL_STATE(79)] = 1329,
  [SMALL_STATE(80)] = 1336,
  [SMALL_STATE(81)] = 1343,
  [SMALL_STATE(82)] = 1350,
  [SMALL_STATE(83)] = 1357,
  [SMALL_STATE(84)] = 1364,
  [SMALL_STATE(85)] = 1371,
  [SMALL_STATE(86)] = 1378,
  [SMALL_STATE(87)] = 1385,
  [SMALL_STATE(88)] = 1390,
  [SMALL_STATE(89)] = 1397,
  [SMALL_STATE(90)] = 1404,
  [SMALL_STATE(91)] = 1411,
  [SMALL_STATE(92)] = 1418,
  [SMALL_STATE(93)] = 1425,
  [SMALL_STATE(94)] = 1432,
  [SMALL_STATE(95)] = 1439,
  [SMALL_STATE(96)] = 1446,
  [SMALL_STATE(97)] = 1453,
  [SMALL_STATE(98)] = 1460,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(91),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [25] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(87),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(98),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0),
  [33] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_comment, 2, 0, 0),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2, 0, 0),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 3, 0, 0),
  [43] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 6, 0, 2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 6, 0, 2),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 7, 0, 3),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 7, 0, 3),
  [51] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 7, 0, 2),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 7, 0, 2),
  [55] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 8, 0, 3),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 8, 0, 3),
  [59] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 4, 0, 0),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(96),
  [63] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(48),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(97),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat3, 2, 0, 0),
  [73] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat3, 2, 0, 0), SHIFT_REPEAT(98),
  [76] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat3, 2, 0, 0), SHIFT_REPEAT(67),
  [79] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat3, 2, 0, 0), SHIFT_REPEAT(64),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [84] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(91),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 5, 0, 0),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(98),
  [92] = {.entry = {.count = 1, .reusable = true}}, SHIFT(92),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [96] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(92),
  [99] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(98),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [106] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(96),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package_declaration, 4, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_package_declaration, 4, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(97),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 3, 0, 0),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 3, 0, 0),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [127] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_path, 1, 0, 0),
  [129] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_include_directive, 2, 0, 0),
  [131] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_include_directive, 2, 0, 0),
  [133] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [137] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_definition, 4, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_definition, 4, 0, 0),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 2, 0, 0),
  [145] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_definition, 5, 0, 0),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 2, 0, 0),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 3, 0, 0),
  [151] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(97),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_definition, 5, 0, 0),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(81),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [162] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 3, 0, 0),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field, 4, 0, 1),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_space_repeat1, 2, 0, 0),
  [174] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_space_repeat1, 2, 0, 0), SHIFT_REPEAT(63),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_space, 1, 0, 0),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [185] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [187] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [189] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [191] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [193] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [195] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [197] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [199] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [201] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_tag, 1, 0, 0),
  [203] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [205] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
  [207] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [209] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [211] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [213] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 1, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_deprecated_tag, 3, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [223] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(95),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [229] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [233] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [235] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [237] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
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
