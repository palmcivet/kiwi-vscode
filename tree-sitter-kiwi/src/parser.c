#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 75
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 48
#define ALIAS_COUNT 0
#define TOKEN_COUNT 21
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

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
  anon_sym_struct = 12,
  sym_deprecated_tag = 13,
  sym_array = 14,
  sym_number = 15,
  anon_sym_DQUOTE = 16,
  anon_sym_SQUOTE = 17,
  aux_sym_path_token1 = 18,
  sym__dir = 19,
  sym__primitive_type = 20,
  sym_source_file = 21,
  sym_include_directive = 22,
  sym_comment = 23,
  sym_package_declaration = 24,
  sym_enum_declaration = 25,
  sym_enum_body = 26,
  sym_enum_field = 27,
  sym_enum_field_name = 28,
  sym_enum_field_value = 29,
  sym_message_declaration = 30,
  sym_message_body = 31,
  sym_message_field = 32,
  sym_message_field_type = 33,
  sym_message_field_name = 34,
  sym_message_field_value = 35,
  sym_struct_declaration = 36,
  sym_struct_body = 37,
  sym_struct_field = 38,
  sym_struct_field_type = 39,
  sym_struct_field_name = 40,
  sym_type_name = 41,
  sym_path = 42,
  aux_sym_source_file_repeat1 = 43,
  aux_sym_source_file_repeat2 = 44,
  aux_sym_enum_body_repeat1 = 45,
  aux_sym_message_body_repeat1 = 46,
  aux_sym_struct_body_repeat1 = 47,
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
  [anon_sym_struct] = "struct",
  [sym_deprecated_tag] = "deprecated_tag",
  [sym_array] = "array",
  [sym_number] = "number",
  [anon_sym_DQUOTE] = "\"",
  [anon_sym_SQUOTE] = "'",
  [aux_sym_path_token1] = "path_token1",
  [sym__dir] = "_dir",
  [sym__primitive_type] = "_primitive_type",
  [sym_source_file] = "source_file",
  [sym_include_directive] = "include_directive",
  [sym_comment] = "comment",
  [sym_package_declaration] = "package_declaration",
  [sym_enum_declaration] = "enum_declaration",
  [sym_enum_body] = "enum_body",
  [sym_enum_field] = "enum_field",
  [sym_enum_field_name] = "enum_field_name",
  [sym_enum_field_value] = "enum_field_value",
  [sym_message_declaration] = "message_declaration",
  [sym_message_body] = "message_body",
  [sym_message_field] = "message_field",
  [sym_message_field_type] = "message_field_type",
  [sym_message_field_name] = "message_field_name",
  [sym_message_field_value] = "message_field_value",
  [sym_struct_declaration] = "struct_declaration",
  [sym_struct_body] = "struct_body",
  [sym_struct_field] = "struct_field",
  [sym_struct_field_type] = "struct_field_type",
  [sym_struct_field_name] = "struct_field_name",
  [sym_type_name] = "type_name",
  [sym_path] = "path",
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
  [anon_sym_struct] = anon_sym_struct,
  [sym_deprecated_tag] = sym_deprecated_tag,
  [sym_array] = sym_array,
  [sym_number] = sym_number,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [anon_sym_SQUOTE] = anon_sym_SQUOTE,
  [aux_sym_path_token1] = aux_sym_path_token1,
  [sym__dir] = sym__dir,
  [sym__primitive_type] = sym__primitive_type,
  [sym_source_file] = sym_source_file,
  [sym_include_directive] = sym_include_directive,
  [sym_comment] = sym_comment,
  [sym_package_declaration] = sym_package_declaration,
  [sym_enum_declaration] = sym_enum_declaration,
  [sym_enum_body] = sym_enum_body,
  [sym_enum_field] = sym_enum_field,
  [sym_enum_field_name] = sym_enum_field_name,
  [sym_enum_field_value] = sym_enum_field_value,
  [sym_message_declaration] = sym_message_declaration,
  [sym_message_body] = sym_message_body,
  [sym_message_field] = sym_message_field,
  [sym_message_field_type] = sym_message_field_type,
  [sym_message_field_name] = sym_message_field_name,
  [sym_message_field_value] = sym_message_field_value,
  [sym_struct_declaration] = sym_struct_declaration,
  [sym_struct_body] = sym_struct_body,
  [sym_struct_field] = sym_struct_field,
  [sym_struct_field_type] = sym_struct_field_type,
  [sym_struct_field_name] = sym_struct_field_name,
  [sym_type_name] = sym_type_name,
  [sym_path] = sym_path,
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
  [anon_sym_struct] = {
    .visible = true,
    .named = false,
  },
  [sym_deprecated_tag] = {
    .visible = true,
    .named = true,
  },
  [sym_array] = {
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
  [sym_enum_field_name] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_field_value] = {
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
  [sym_message_field_type] = {
    .visible = true,
    .named = true,
  },
  [sym_message_field_name] = {
    .visible = true,
    .named = true,
  },
  [sym_message_field_value] = {
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
  [sym_struct_field_type] = {
    .visible = true,
    .named = true,
  },
  [sym_struct_field_name] = {
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(27);
      ADVANCE_MAP(
        '"', 69,
        '\'', 71,
        '/', 4,
        ';', 37,
        '=', 40,
        '[', 8,
        'b', 58,
        'd', 56,
        'f', 53,
        'i', 55,
        's', 62,
        'u', 49,
        '{', 38,
        '}', 39,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(7);
      END_STATE();
    case 2:
      if (lookahead == ' ') ADVANCE(28);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(70);
      if (lookahead == '\'') ADVANCE(72);
      if (lookahead == '/') ADVANCE(73);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      if (lookahead != 0) ADVANCE(74);
      END_STATE();
    case 4:
      if (lookahead == '/') ADVANCE(30);
      END_STATE();
    case 5:
      if (lookahead == '/') ADVANCE(29);
      END_STATE();
    case 6:
      if (lookahead == '/') ADVANCE(75);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(76);
      END_STATE();
    case 7:
      if (lookahead == '@') ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == ']') ADVANCE(67);
      if (lookahead == 'd') ADVANCE(15);
      END_STATE();
    case 9:
      if (lookahead == ']') ADVANCE(41);
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
      if (eof) ADVANCE(27);
      ADVANCE_MAP(
        '"', 69,
        '\'', 71,
        '/', 5,
        ';', 37,
        '=', 40,
        '[', 8,
        'b', 58,
        'd', 56,
        'f', 53,
        'i', 55,
        's', 62,
        'u', 49,
        '{', 38,
        '}', 39,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(26);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH_SLASH_ATinclude);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead == '/') ADVANCE(1);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(76);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(74);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_SLASH_SLASH);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(36);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '/') ADVANCE(35);
      if (lookahead == '\t' ||
          (0x0b <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') ADVANCE(34);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead)) ADVANCE(36);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead == '/') ADVANCE(33);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(36);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(aux_sym_comment_token1);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(36);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_deprecated_tag);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '2') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '3') ADVANCE(42);
      if (lookahead == '6') ADVANCE(44);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '4') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(61);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'b') ADVANCE(52);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'g') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(54);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(57);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(48);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(64);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(65);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(45);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(59);
      if (lookahead == 'y') ADVANCE(63);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(51);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(66);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(60);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(47);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(46);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(66);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_array);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(74);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(anon_sym_SQUOTE);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(74);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(aux_sym_path_token1);
      if (lookahead == '/') ADVANCE(32);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(74);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(aux_sym_path_token1);
      if (lookahead != 0 &&
          (lookahead < '\t' || '\r' < lookahead) &&
          lookahead != ' ') ADVANCE(74);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym__dir);
      if (lookahead == '/') ADVANCE(31);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(76);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym__dir);
      if (('-' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(76);
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
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
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
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 26},
  [6] = {.lex_state = 26},
  [7] = {.lex_state = 26},
  [8] = {.lex_state = 26},
  [9] = {.lex_state = 26},
  [10] = {.lex_state = 26},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 26},
  [13] = {.lex_state = 26},
  [14] = {.lex_state = 26},
  [15] = {.lex_state = 26},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 26},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 26},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 26},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 3},
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
  [51] = {.lex_state = 6},
  [52] = {.lex_state = 26},
  [53] = {.lex_state = 6},
  [54] = {.lex_state = 26},
  [55] = {.lex_state = 26},
  [56] = {.lex_state = 26},
  [57] = {.lex_state = 26},
  [58] = {.lex_state = 26},
  [59] = {.lex_state = 26},
  [60] = {.lex_state = 26},
  [61] = {.lex_state = 26},
  [62] = {.lex_state = 26},
  [63] = {.lex_state = 26},
  [64] = {.lex_state = 34},
  [65] = {.lex_state = 26},
  [66] = {.lex_state = 26},
  [67] = {.lex_state = 26},
  [68] = {.lex_state = 26},
  [69] = {.lex_state = 26},
  [70] = {.lex_state = 26},
  [71] = {.lex_state = 26},
  [72] = {.lex_state = 26},
  [73] = {.lex_state = 26},
  [74] = {(TSStateId)(-1)},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [sym_comment] = STATE(0),
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SLASH_SLASH_SLASH_ATinclude] = ACTIONS(1),
    [anon_sym_SLASH_SLASH] = ACTIONS(3),
    [anon_sym_package] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_message] = ACTIONS(1),
    [anon_sym_struct] = ACTIONS(1),
    [sym_deprecated_tag] = ACTIONS(1),
    [sym_array] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [anon_sym_SQUOTE] = ACTIONS(1),
    [sym__primitive_type] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(63),
    [sym_include_directive] = STATE(18),
    [sym_comment] = STATE(1),
    [sym_package_declaration] = STATE(2),
    [sym_enum_declaration] = STATE(26),
    [sym_message_declaration] = STATE(26),
    [sym_struct_declaration] = STATE(26),
    [aux_sym_source_file_repeat1] = STATE(4),
    [aux_sym_source_file_repeat2] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(5),
    [anon_sym_SLASH_SLASH_SLASH_ATinclude] = ACTIONS(7),
    [anon_sym_SLASH_SLASH] = ACTIONS(3),
    [anon_sym_package] = ACTIONS(9),
    [anon_sym_enum] = ACTIONS(11),
    [anon_sym_message] = ACTIONS(13),
    [anon_sym_struct] = ACTIONS(15),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 11,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      sym_comment,
    STATE(3), 1,
      aux_sym_source_file_repeat1,
    STATE(6), 1,
      aux_sym_source_file_repeat2,
    STATE(18), 1,
      sym_include_directive,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [36] = 11,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    STATE(3), 1,
      sym_comment,
    STATE(8), 1,
      aux_sym_source_file_repeat2,
    STATE(11), 1,
      aux_sym_source_file_repeat1,
    STATE(18), 1,
      sym_include_directive,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [72] = 11,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(7), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    STATE(4), 1,
      sym_comment,
    STATE(6), 1,
      aux_sym_source_file_repeat2,
    STATE(11), 1,
      aux_sym_source_file_repeat1,
    STATE(18), 1,
      sym_include_directive,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [108] = 8,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(17), 1,
      ts_builtin_sym_end,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(5), 1,
      sym_comment,
    STATE(7), 1,
      aux_sym_source_file_repeat2,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [135] = 8,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(19), 1,
      ts_builtin_sym_end,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(6), 1,
      sym_comment,
    STATE(7), 1,
      aux_sym_source_file_repeat2,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [162] = 7,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(23), 1,
      ts_builtin_sym_end,
    ACTIONS(25), 1,
      anon_sym_enum,
    ACTIONS(28), 1,
      anon_sym_message,
    ACTIONS(31), 1,
      anon_sym_struct,
    STATE(7), 2,
      sym_comment,
      aux_sym_source_file_repeat2,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [187] = 8,
    ACTIONS(11), 1,
      anon_sym_enum,
    ACTIONS(13), 1,
      anon_sym_message,
    ACTIONS(15), 1,
      anon_sym_struct,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(34), 1,
      ts_builtin_sym_end,
    STATE(7), 1,
      aux_sym_source_file_repeat2,
    STATE(8), 1,
      sym_comment,
    STATE(26), 3,
      sym_enum_declaration,
      sym_message_declaration,
      sym_struct_declaration,
  [214] = 9,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(36), 1,
      sym_identifier,
    ACTIONS(38), 1,
      anon_sym_RBRACE,
    ACTIONS(40), 1,
      sym__primitive_type,
    STATE(9), 1,
      sym_comment,
    STATE(13), 1,
      aux_sym_struct_body_repeat1,
    STATE(36), 1,
      sym_struct_field,
    STATE(42), 1,
      sym_struct_field_type,
    STATE(52), 1,
      sym_type_name,
  [242] = 9,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(36), 1,
      sym_identifier,
    ACTIONS(40), 1,
      sym__primitive_type,
    ACTIONS(42), 1,
      anon_sym_RBRACE,
    STATE(10), 1,
      sym_comment,
    STATE(12), 1,
      aux_sym_message_body_repeat1,
    STATE(35), 1,
      sym_message_field,
    STATE(39), 1,
      sym_message_field_type,
    STATE(68), 1,
      sym_type_name,
  [270] = 5,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(46), 1,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
    STATE(18), 1,
      sym_include_directive,
    STATE(11), 2,
      sym_comment,
      aux_sym_source_file_repeat1,
    ACTIONS(44), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [290] = 9,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(36), 1,
      sym_identifier,
    ACTIONS(40), 1,
      sym__primitive_type,
    ACTIONS(49), 1,
      anon_sym_RBRACE,
    STATE(12), 1,
      sym_comment,
    STATE(14), 1,
      aux_sym_message_body_repeat1,
    STATE(35), 1,
      sym_message_field,
    STATE(39), 1,
      sym_message_field_type,
    STATE(68), 1,
      sym_type_name,
  [318] = 9,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(36), 1,
      sym_identifier,
    ACTIONS(40), 1,
      sym__primitive_type,
    ACTIONS(51), 1,
      anon_sym_RBRACE,
    STATE(13), 1,
      sym_comment,
    STATE(15), 1,
      aux_sym_struct_body_repeat1,
    STATE(36), 1,
      sym_struct_field,
    STATE(42), 1,
      sym_struct_field_type,
    STATE(52), 1,
      sym_type_name,
  [346] = 8,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(53), 1,
      sym_identifier,
    ACTIONS(56), 1,
      anon_sym_RBRACE,
    ACTIONS(58), 1,
      sym__primitive_type,
    STATE(35), 1,
      sym_message_field,
    STATE(39), 1,
      sym_message_field_type,
    STATE(68), 1,
      sym_type_name,
    STATE(14), 2,
      sym_comment,
      aux_sym_message_body_repeat1,
  [372] = 8,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(61), 1,
      sym_identifier,
    ACTIONS(64), 1,
      anon_sym_RBRACE,
    ACTIONS(66), 1,
      sym__primitive_type,
    STATE(36), 1,
      sym_struct_field,
    STATE(42), 1,
      sym_struct_field_type,
    STATE(52), 1,
      sym_type_name,
    STATE(15), 2,
      sym_comment,
      aux_sym_struct_body_repeat1,
  [398] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    STATE(16), 1,
      sym_comment,
    ACTIONS(69), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [412] = 7,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(71), 1,
      sym_identifier,
    ACTIONS(73), 1,
      anon_sym_RBRACE,
    STATE(17), 1,
      sym_comment,
    STATE(19), 1,
      aux_sym_enum_body_repeat1,
    STATE(40), 1,
      sym_enum_field,
    STATE(59), 1,
      sym_enum_field_name,
  [434] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    STATE(18), 1,
      sym_comment,
    ACTIONS(75), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [448] = 7,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(71), 1,
      sym_identifier,
    ACTIONS(77), 1,
      anon_sym_RBRACE,
    STATE(19), 1,
      sym_comment,
    STATE(21), 1,
      aux_sym_enum_body_repeat1,
    STATE(40), 1,
      sym_enum_field,
    STATE(59), 1,
      sym_enum_field_name,
  [470] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    STATE(20), 1,
      sym_comment,
    ACTIONS(79), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [484] = 6,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(81), 1,
      sym_identifier,
    ACTIONS(84), 1,
      anon_sym_RBRACE,
    STATE(40), 1,
      sym_enum_field,
    STATE(59), 1,
      sym_enum_field_name,
    STATE(21), 2,
      sym_comment,
      aux_sym_enum_body_repeat1,
  [504] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    STATE(22), 1,
      sym_comment,
    ACTIONS(86), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [518] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    STATE(23), 1,
      sym_comment,
    ACTIONS(88), 5,
      ts_builtin_sym_end,
      anon_sym_SLASH_SLASH_SLASH_ATinclude,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [532] = 6,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(90), 1,
      anon_sym_DQUOTE,
    ACTIONS(92), 1,
      anon_sym_SQUOTE,
    ACTIONS(94), 1,
      aux_sym_path_token1,
    STATE(22), 1,
      sym_path,
    STATE(24), 1,
      sym_comment,
  [551] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(25), 1,
      sym_comment,
    ACTIONS(96), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [564] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(26), 1,
      sym_comment,
    ACTIONS(98), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [577] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(27), 1,
      sym_comment,
    ACTIONS(100), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [590] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(28), 1,
      sym_comment,
    ACTIONS(102), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [603] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(29), 1,
      sym_comment,
    ACTIONS(104), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [616] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(30), 1,
      sym_comment,
    ACTIONS(106), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [629] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(31), 1,
      sym_comment,
    ACTIONS(108), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [642] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(32), 1,
      sym_comment,
    ACTIONS(110), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [655] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(33), 1,
      sym_comment,
    ACTIONS(112), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [668] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(34), 1,
      sym_comment,
    ACTIONS(114), 4,
      ts_builtin_sym_end,
      anon_sym_enum,
      anon_sym_message,
      anon_sym_struct,
  [681] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(118), 1,
      sym__primitive_type,
    STATE(35), 1,
      sym_comment,
    ACTIONS(116), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [695] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(122), 1,
      sym__primitive_type,
    STATE(36), 1,
      sym_comment,
    ACTIONS(120), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [709] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(126), 1,
      sym__primitive_type,
    STATE(37), 1,
      sym_comment,
    ACTIONS(124), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [723] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(130), 1,
      sym__primitive_type,
    STATE(38), 1,
      sym_comment,
    ACTIONS(128), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [737] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(132), 1,
      sym_identifier,
    STATE(39), 1,
      sym_comment,
    STATE(54), 1,
      sym_message_field_name,
  [750] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(40), 1,
      sym_comment,
    ACTIONS(134), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [761] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(136), 1,
      sym_identifier,
    ACTIONS(138), 1,
      sym_array,
    STATE(41), 1,
      sym_comment,
  [774] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(140), 1,
      sym_identifier,
    STATE(42), 1,
      sym_comment,
    STATE(62), 1,
      sym_struct_field_name,
  [787] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(142), 1,
      anon_sym_LBRACE,
    STATE(27), 1,
      sym_message_body,
    STATE(43), 1,
      sym_comment,
  [800] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(144), 1,
      anon_sym_LBRACE,
    STATE(32), 1,
      sym_struct_body,
    STATE(44), 1,
      sym_comment,
  [813] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(146), 1,
      sym_number,
    STATE(45), 1,
      sym_comment,
    STATE(71), 1,
      sym_message_field_value,
  [826] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(148), 1,
      anon_sym_LBRACE,
    STATE(25), 1,
      sym_enum_body,
    STATE(46), 1,
      sym_comment,
  [839] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    STATE(47), 1,
      sym_comment,
    ACTIONS(150), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [850] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(152), 1,
      anon_sym_SEMI,
    ACTIONS(154), 1,
      sym_deprecated_tag,
    STATE(48), 1,
      sym_comment,
  [863] = 4,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(156), 1,
      sym_number,
    STATE(49), 1,
      sym_comment,
    STATE(50), 1,
      sym_enum_field_value,
  [876] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(158), 1,
      anon_sym_SEMI,
    STATE(50), 1,
      sym_comment,
  [886] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(160), 1,
      sym__dir,
    STATE(51), 1,
      sym_comment,
  [896] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(162), 1,
      sym_identifier,
    STATE(52), 1,
      sym_comment,
  [906] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(164), 1,
      sym__dir,
    STATE(53), 1,
      sym_comment,
  [916] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(166), 1,
      anon_sym_EQ,
    STATE(54), 1,
      sym_comment,
  [926] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(168), 1,
      anon_sym_EQ,
    STATE(55), 1,
      sym_comment,
  [936] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(170), 1,
      anon_sym_DQUOTE,
    STATE(56), 1,
      sym_comment,
  [946] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(172), 1,
      sym_identifier,
    STATE(57), 1,
      sym_comment,
  [956] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(174), 1,
      anon_sym_EQ,
    STATE(58), 1,
      sym_comment,
  [966] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(176), 1,
      anon_sym_EQ,
    STATE(59), 1,
      sym_comment,
  [976] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(170), 1,
      anon_sym_SQUOTE,
    STATE(60), 1,
      sym_comment,
  [986] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(178), 1,
      anon_sym_SEMI,
    STATE(61), 1,
      sym_comment,
  [996] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(180), 1,
      anon_sym_SEMI,
    STATE(62), 1,
      sym_comment,
  [1006] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(182), 1,
      ts_builtin_sym_end,
    STATE(63), 1,
      sym_comment,
  [1016] = 3,
    ACTIONS(3), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(184), 1,
      aux_sym_comment_token1,
    STATE(64), 1,
      sym_comment,
  [1026] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(186), 1,
      anon_sym_SEMI,
    STATE(65), 1,
      sym_comment,
  [1036] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(188), 1,
      anon_sym_SEMI,
    STATE(66), 1,
      sym_comment,
  [1046] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(190), 1,
      sym_identifier,
    STATE(67), 1,
      sym_comment,
  [1056] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(192), 1,
      sym_identifier,
    STATE(68), 1,
      sym_comment,
  [1066] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(194), 1,
      sym_identifier,
    STATE(69), 1,
      sym_comment,
  [1076] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(196), 1,
      sym_identifier,
    STATE(70), 1,
      sym_comment,
  [1086] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(198), 1,
      anon_sym_SEMI,
    STATE(71), 1,
      sym_comment,
  [1096] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(200), 1,
      anon_sym_SEMI,
    STATE(72), 1,
      sym_comment,
  [1106] = 3,
    ACTIONS(21), 1,
      anon_sym_SLASH_SLASH,
    ACTIONS(202), 1,
      sym_identifier,
    STATE(73), 1,
      sym_comment,
  [1116] = 1,
    ACTIONS(204), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 36,
  [SMALL_STATE(4)] = 72,
  [SMALL_STATE(5)] = 108,
  [SMALL_STATE(6)] = 135,
  [SMALL_STATE(7)] = 162,
  [SMALL_STATE(8)] = 187,
  [SMALL_STATE(9)] = 214,
  [SMALL_STATE(10)] = 242,
  [SMALL_STATE(11)] = 270,
  [SMALL_STATE(12)] = 290,
  [SMALL_STATE(13)] = 318,
  [SMALL_STATE(14)] = 346,
  [SMALL_STATE(15)] = 372,
  [SMALL_STATE(16)] = 398,
  [SMALL_STATE(17)] = 412,
  [SMALL_STATE(18)] = 434,
  [SMALL_STATE(19)] = 448,
  [SMALL_STATE(20)] = 470,
  [SMALL_STATE(21)] = 484,
  [SMALL_STATE(22)] = 504,
  [SMALL_STATE(23)] = 518,
  [SMALL_STATE(24)] = 532,
  [SMALL_STATE(25)] = 551,
  [SMALL_STATE(26)] = 564,
  [SMALL_STATE(27)] = 577,
  [SMALL_STATE(28)] = 590,
  [SMALL_STATE(29)] = 603,
  [SMALL_STATE(30)] = 616,
  [SMALL_STATE(31)] = 629,
  [SMALL_STATE(32)] = 642,
  [SMALL_STATE(33)] = 655,
  [SMALL_STATE(34)] = 668,
  [SMALL_STATE(35)] = 681,
  [SMALL_STATE(36)] = 695,
  [SMALL_STATE(37)] = 709,
  [SMALL_STATE(38)] = 723,
  [SMALL_STATE(39)] = 737,
  [SMALL_STATE(40)] = 750,
  [SMALL_STATE(41)] = 761,
  [SMALL_STATE(42)] = 774,
  [SMALL_STATE(43)] = 787,
  [SMALL_STATE(44)] = 800,
  [SMALL_STATE(45)] = 813,
  [SMALL_STATE(46)] = 826,
  [SMALL_STATE(47)] = 839,
  [SMALL_STATE(48)] = 850,
  [SMALL_STATE(49)] = 863,
  [SMALL_STATE(50)] = 876,
  [SMALL_STATE(51)] = 886,
  [SMALL_STATE(52)] = 896,
  [SMALL_STATE(53)] = 906,
  [SMALL_STATE(54)] = 916,
  [SMALL_STATE(55)] = 926,
  [SMALL_STATE(56)] = 936,
  [SMALL_STATE(57)] = 946,
  [SMALL_STATE(58)] = 956,
  [SMALL_STATE(59)] = 966,
  [SMALL_STATE(60)] = 976,
  [SMALL_STATE(61)] = 986,
  [SMALL_STATE(62)] = 996,
  [SMALL_STATE(63)] = 1006,
  [SMALL_STATE(64)] = 1016,
  [SMALL_STATE(65)] = 1026,
  [SMALL_STATE(66)] = 1036,
  [SMALL_STATE(67)] = 1046,
  [SMALL_STATE(68)] = 1056,
  [SMALL_STATE(69)] = 1066,
  [SMALL_STATE(70)] = 1076,
  [SMALL_STATE(71)] = 1086,
  [SMALL_STATE(72)] = 1096,
  [SMALL_STATE(73)] = 1106,
  [SMALL_STATE(74)] = 1116,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(69),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(70),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(73),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 3, 0, 0),
  [36] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [40] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [46] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(24),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [53] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0),
  [58] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [61] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0),
  [66] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_struct_body_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 3, 0, 0),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_path, 1, 0, 0),
  [81] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0), SHIFT_REPEAT(55),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 2, 0, 0),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_include_directive, 2, 0, 0),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_package_declaration, 3, 0, 0),
  [90] = {.entry = {.count = 1, .reusable = false}}, SHIFT(53),
  [92] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [94] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_declaration, 3, 0, 0),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 1, 0, 0),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_declaration, 3, 0, 0),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 2, 0, 0),
  [104] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_body, 2, 0, 0),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_body, 3, 0, 0),
  [108] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 3, 0, 0),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_declaration, 3, 0, 0),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_body, 3, 0, 0),
  [114] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_body, 2, 0, 0),
  [116] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_message_body_repeat1, 1, 0, 0),
  [118] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_message_body_repeat1, 1, 0, 0),
  [120] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_struct_body_repeat1, 1, 0, 0),
  [122] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_struct_body_repeat1, 1, 0, 0),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field, 5, 0, 0),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_message_field, 5, 0, 0),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_field, 3, 0, 0),
  [130] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_struct_field, 3, 0, 0),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_body_repeat1, 1, 0, 0),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 1, 0, 0),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field, 4, 0, 0),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field_value, 1, 0, 0),
  [154] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [160] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_field_type, 1, 0, 0),
  [164] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field_name, 1, 0, 0),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_name, 2, 0, 0),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field_name, 1, 0, 0),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [178] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_field_name, 1, 0, 0),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [182] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [184] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [186] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_field_value, 1, 0, 0),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field_type, 1, 0, 0),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [198] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_message_field_value, 2, 0, 0),
  [202] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [204] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comment, 2, 0, 0),
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
