ifndef __G_SCANNER_H__
define __G_SCANNER_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gdataset.inc
include glib/ghash.inc

CALLBACK(GScannerMsgFunc, :ptr, :ptr, :gboolean)

define G_CSET_A_2_Z	<"ABCDEFGHIJKLMNOPQRSTUVWXYZ">
define G_CSET_a_2_z	<"abcdefghijklmnopqrstuvwxyz">
define G_CSET_DIGITS	<"0123456789">
define G_CSET_LATINC	<"\300\301\302\303\304\305\306"				"\307\310\311\312\313\314\315\316\317\320"			"\321\322\323\324\325\326"			"\330\331\332\333\334\335\336">
define G_CSET_LATINS	<"\337\340\341\342\343\344\345\346"			"\347\350\351\352\353\354\355\356\357\360"			"\361\362\363\364\365\366"			"\370\371\372\373\374\375\376\377">


.enum GErrorType {
  G_ERR_UNKNOWN,
  G_ERR_UNEXP_EOF,
  G_ERR_UNEXP_EOF_IN_STRING,
  G_ERR_UNEXP_EOF_IN_COMMENT,
  G_ERR_NON_DIGIT_IN_CONST,
  G_ERR_DIGIT_RADIX,
  G_ERR_FLOAT_RADIX,
  G_ERR_FLOAT_MALFORMED
}


.enum GTokenType {
  G_TOKEN_EOF			=   0,

  G_TOKEN_LEFT_PAREN		= '(',
  G_TOKEN_RIGHT_PAREN		= ')',
  G_TOKEN_LEFT_CURLY		= '{',
  G_TOKEN_RIGHT_CURLY		= '}',
  G_TOKEN_LEFT_BRACE		= '[',
  G_TOKEN_RIGHT_BRACE		= ']',
  G_TOKEN_EQUAL_SIGN		= '=',
  G_TOKEN_COMMA			= ',',

  G_TOKEN_NONE			= 256,

  G_TOKEN_ERROR,

  G_TOKEN_CHAR,
  G_TOKEN_BINARY,
  G_TOKEN_OCTAL,
  G_TOKEN_INT,
  G_TOKEN_HEX,
  G_TOKEN_FLOAT,
  G_TOKEN_STRING,

  G_TOKEN_SYMBOL,
  G_TOKEN_IDENTIFIER,
  G_TOKEN_IDENTIFIER_NULL,

  G_TOKEN_COMMENT_SINGLE,
  G_TOKEN_COMMENT_MULTI,


  G_TOKEN_LAST
}

_GTokenValue		union
v_symbol		gpointer ?
v_identifier		ptr gchar ?
v_binary		gulong ?
v_octal			gulong ?
v_int			gulong ?
v_int64			guint64 ?
v_float			gdouble ?
v_hex			gulong ?
v_string		ptr gchar ?
v_comment		ptr gchar ?
v_char			guchar ?
v_error			guint ?
_GTokenValue		ends
GTokenValue		typedef _GTokenValue

_GScannerConfig		struct
cset_skip_characters	ptr gchar ?
cset_identifier_first	ptr gchar ?
cset_identifier_nth	ptr gchar ?
cpair_comment_single	ptr gchar ?
RECORD
case_sensitive		guint :	 1 ?
skip_comment_multi	guint :	 1 ?
skip_comment_single	guint :	 1 ?
scan_comment_multi	guint :	 1 ?
scan_identifier		guint :	 1 ?
scan_identifier_1char	guint :	 1 ?
scan_identifier_NULL	guint :	 1 ?
scan_symbols		guint :	 1 ?
scan_binary		guint :	 1 ?
scan_octal		guint :	 1 ?
scan_float		guint :	 1 ?
scan_hex		guint :	 1 ?
scan_hex_dollar		guint :	 1 ?
scan_string_sq		guint :	 1 ?
scan_string_dq		guint :	 1 ?
numbers_2_int		guint :	 1 ?
int_2_float		guint :	 1 ?
identifier_2_string	guint :	 1 ?
char_2_token		guint :	 1 ?
symbol_2_token		guint :	 1 ?
scope_0_fallback	guint :	 1 ?
store_int64		guint :	 1 ?
ENDS
padding_dummy		guint ?
_GScannerConfig		ends
GScannerConfig		typedef _GScannerConfig

_GScanner		struct
user_data		gpointer ?
max_parse_errors	guint ?
parse_errors		guint ?
input_name		ptr gchar ?
qdata			ptr GData ?
config			ptr GScannerConfig ?
token			GTokenType ?
value			GTokenValue <>
line			guint ?
position		guint ?
next_token		GTokenType ?
next_value		GTokenValue <>
next_line		guint ?
next_position		guint ?
symbol_table		ptr GHashTable ?
input_fd		gint ?
text			ptr gchar ?
text_end		ptr gchar ?
buffer			ptr gchar ?
scope_id		guint ?
msg_handler		GScannerMsgFunc ?
_GScanner		ends
GScanner		typedef _GScanner

g_scanner_new proto :ptr
g_scanner_destroy proto :ptr
g_scanner_input_file proto :ptr, :gint
g_scanner_sync_file_offset proto :ptr
g_scanner_input_text proto :ptr, :ptr, :guint
g_scanner_get_next_token proto :ptr
g_scanner_peek_next_token proto :ptr
g_scanner_cur_token proto :ptr
g_scanner_cur_value proto :ptr
g_scanner_cur_line proto :ptr
g_scanner_cur_position proto :ptr
g_scanner_eof proto :ptr
g_scanner_set_scope proto :ptr, :guint
g_scanner_scope_add_symbol proto :ptr, :guint, :ptr, :gpointer
g_scanner_scope_remove_symbol proto :ptr, :guint, :ptr
g_scanner_scope_lookup_symbol proto :ptr, :guint, :ptr
g_scanner_scope_foreach_symbol proto :ptr, :guint, :GHFunc, :gpointer
g_scanner_lookup_symbol proto :ptr, :ptr
g_scanner_unexp_token proto :ptr, :GTokenType, :ptr, :ptr, :ptr, :ptr, :gint


g_scanner_add_symbol macro  scanner, symbol, value
  exitm<.err>
  endm
g_scanner_remove_symbol macro  scanner, symbol
  exitm<.err>
  endm
g_scanner_foreach_symbol macro	scanner, func, data
  exitm<>
  endm


g_scanner_freeze_symbol_table macro scanner
  exitm<(0)>
  endm
g_scanner_thaw_symbol_table macro scanner
  exitm<(0)>
  endm

endif
