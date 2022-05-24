ifndef __G_STRFUNCS_H__
define __G_STRFUNCS_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stdarg.inc
include glib/gmacros.inc
include glib/gtypes.inc
include glib/gerror.inc

.enum GAsciiType {
  G_ASCII_ALNUM	 = 1 shl 0,
  G_ASCII_ALPHA	 = 1 shl 1,
  G_ASCII_CNTRL	 = 1 shl 2,
  G_ASCII_DIGIT	 = 1 shl 3,
  G_ASCII_GRAPH	 = 1 shl 4,
  G_ASCII_LOWER	 = 1 shl 5,
  G_ASCII_PRINT	 = 1 shl 6,
  G_ASCII_PUNCT	 = 1 shl 7,
  G_ASCII_SPACE	 = 1 shl 8,
  G_ASCII_UPPER	 = 1 shl 9,
  G_ASCII_XDIGIT = 1 shl 10
}


g_ascii_isalnum macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_ALNUM) != 0)>
  endm

g_ascii_isalpha macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_ALPHA) != 0)>
  endm

g_ascii_iscntrl macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_CNTRL) != 0)>
  endm

g_ascii_isdigit macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_DIGIT) != 0)>
  endm

g_ascii_isgraph macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_GRAPH) != 0)>
  endm

g_ascii_islower macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_LOWER) != 0)>
  endm

g_ascii_isprint macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_PRINT) != 0)>
  endm

g_ascii_ispunct macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_PUNCT) != 0)>
  endm

g_ascii_isspace macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_SPACE) != 0)>
  endm

g_ascii_isupper macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_UPPER) != 0)>
  endm

g_ascii_isxdigit macro c
  exitm<((g_ascii_table[(c)] & G_ASCII_XDIGIT) != 0)>
  endm

g_ascii_tolower proto :gchar
g_ascii_toupper proto :gchar

g_ascii_digit_value proto :gchar
g_ascii_xdigit_value proto :gchar

define G_STR_DELIMITERS <"_-|!> !<.">

g_strdelimit proto :ptr, :ptr, :gchar
g_strcanon proto :ptr, :ptr, :gchar
g_strerror proto :gint
g_strsignal proto :gint
g_strreverse proto :ptr
g_strlcpy proto :ptr, :ptr, :gsize
g_strlcat proto :ptr, :ptr, :gsize
g_strstr_len proto :ptr, :gssize, :ptr
g_strrstr proto :ptr, :ptr
g_strrstr_len proto :ptr, :gssize, :ptr

g_str_has_suffix proto :ptr, :ptr
g_str_has_prefix proto :ptr, :ptr

g_strtod proto :ptr, :ptr
g_ascii_strtod proto :ptr, :ptr
g_ascii_strtoull proto :ptr, :ptr, :guint
g_ascii_strtoll proto :ptr, :ptr, :guint

define G_ASCII_DTOSTR_BUF_SIZE (29 + 10)
g_ascii_dtostr proto :ptr, :gint, :gdouble
g_ascii_formatd proto :ptr, :gint, :ptr, :gdouble
g_strchug proto :ptr
g_strchomp proto :ptr

g_strstrip macro  string
  exitm<g_strchomp (g_strchug (string))>
  endm

g_ascii_strcasecmp proto :ptr, :ptr
g_ascii_strncasecmp proto :ptr, :ptr, :gsize
g_ascii_strdown proto :ptr, :gssize
g_ascii_strup proto :ptr, :gssize

g_str_is_ascii proto :ptr

g_strcasecmp proto :ptr, :ptr
g_strncasecmp proto :ptr, :ptr, :guint
g_strdown proto :ptr
g_strup proto :ptr

g_strdup proto :ptr
g_strdup_printf proto :ptr, :vararg
g_strdup_vprintf proto :ptr, :va_list
g_strndup proto :ptr, :gsize
g_strnfill proto :gsize, :gchar
g_strconcat proto :ptr, :vararg
g_strjoin proto :ptr, :vararg

g_strcompress proto :ptr
g_strescape proto :ptr, :ptr
g_memdup proto :gconstpointer, :guint
g_memdup2 proto :gconstpointer, :gsize

GStrv typedef ptr gchar
g_strsplit proto :ptr, :ptr, :gint
g_strsplit_set proto :ptr, :ptr, :gint
g_strjoinv proto :ptr, :ptr
g_strfreev proto :ptr
g_strdupv proto :ptr
g_strv_length proto :ptr
g_stpcpy proto :ptr, :ptr
g_str_to_ascii proto :ptr, :ptr
g_str_tokenize_and_fold proto :ptr, :ptr, :ptr
g_str_match_string proto :ptr, :ptr, :gboolean
g_strv_contains proto :ptr, :ptr
g_strv_equal proto :ptr, :ptr

.enum GNumberParserError {
    G_NUMBER_PARSER_ERROR_INVALID,
    G_NUMBER_PARSER_ERROR_OUT_OF_BOUNDS,
  }

define G_NUMBER_PARSER_ERROR (g_number_parser_error_quark ())

g_number_parser_error_quark proto
g_ascii_string_to_signed proto :ptr, :guint, :gint64, :gint64, :ptr, :ptr
g_ascii_string_to_unsigned proto :ptr, :guint, :guint64, :guint64, :ptr, :ptr

endif
