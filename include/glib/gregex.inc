ifndef __G_REGEX_H__
define __G_REGEX_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc
include glib/gstring.inc

.enum GRegexError {
  G_REGEX_ERROR_COMPILE,
  G_REGEX_ERROR_OPTIMIZE,
  G_REGEX_ERROR_REPLACE,
  G_REGEX_ERROR_MATCH,
  G_REGEX_ERROR_INTERNAL,


  G_REGEX_ERROR_STRAY_BACKSLASH = 101,
  G_REGEX_ERROR_MISSING_CONTROL_CHAR = 102,
  G_REGEX_ERROR_UNRECOGNIZED_ESCAPE = 103,
  G_REGEX_ERROR_QUANTIFIERS_OUT_OF_ORDER = 104,
  G_REGEX_ERROR_QUANTIFIER_TOO_BIG = 105,
  G_REGEX_ERROR_UNTERMINATED_CHARACTER_CLASS = 106,
  G_REGEX_ERROR_INVALID_ESCAPE_IN_CHARACTER_CLASS = 107,
  G_REGEX_ERROR_RANGE_OUT_OF_ORDER = 108,
  G_REGEX_ERROR_NOTHING_TO_REPEAT = 109,
  G_REGEX_ERROR_UNRECOGNIZED_CHARACTER = 112,
  G_REGEX_ERROR_POSIX_NAMED_CLASS_OUTSIDE_CLASS = 113,
  G_REGEX_ERROR_UNMATCHED_PARENTHESIS = 114,
  G_REGEX_ERROR_INEXISTENT_SUBPATTERN_REFERENCE = 115,
  G_REGEX_ERROR_UNTERMINATED_COMMENT = 118,
  G_REGEX_ERROR_EXPRESSION_TOO_LARGE = 120,
  G_REGEX_ERROR_MEMORY_ERROR = 121,
  G_REGEX_ERROR_VARIABLE_LENGTH_LOOKBEHIND = 125,
  G_REGEX_ERROR_MALFORMED_CONDITION = 126,
  G_REGEX_ERROR_TOO_MANY_CONDITIONAL_BRANCHES = 127,
  G_REGEX_ERROR_ASSERTION_EXPECTED = 128,
  G_REGEX_ERROR_UNKNOWN_POSIX_CLASS_NAME = 130,
  G_REGEX_ERROR_POSIX_COLLATING_ELEMENTS_NOT_SUPPORTED = 131,
  G_REGEX_ERROR_HEX_CODE_TOO_LARGE = 134,
  G_REGEX_ERROR_INVALID_CONDITION = 135,
  G_REGEX_ERROR_SINGLE_BYTE_MATCH_IN_LOOKBEHIND = 136,
  G_REGEX_ERROR_INFINITE_LOOP = 140,
  G_REGEX_ERROR_MISSING_SUBPATTERN_NAME_TERMINATOR = 142,
  G_REGEX_ERROR_DUPLICATE_SUBPATTERN_NAME = 143,
  G_REGEX_ERROR_MALFORMED_PROPERTY = 146,
  G_REGEX_ERROR_UNKNOWN_PROPERTY = 147,
  G_REGEX_ERROR_SUBPATTERN_NAME_TOO_LONG = 148,
  G_REGEX_ERROR_TOO_MANY_SUBPATTERNS = 149,
  G_REGEX_ERROR_INVALID_OCTAL_VALUE = 151,
  G_REGEX_ERROR_TOO_MANY_BRANCHES_IN_DEFINE = 154,
  G_REGEX_ERROR_DEFINE_REPETION = 155,
  G_REGEX_ERROR_INCONSISTENT_NEWLINE_OPTIONS = 156,
  G_REGEX_ERROR_MISSING_BACK_REFERENCE = 157,
  G_REGEX_ERROR_INVALID_RELATIVE_REFERENCE = 158,
  G_REGEX_ERROR_BACKTRACKING_CONTROL_VERB_ARGUMENT_FORBIDDEN = 159,
  G_REGEX_ERROR_UNKNOWN_BACKTRACKING_CONTROL_VERB  = 160,
  G_REGEX_ERROR_NUMBER_TOO_BIG = 161,
  G_REGEX_ERROR_MISSING_SUBPATTERN_NAME = 162,
  G_REGEX_ERROR_MISSING_DIGIT = 163,
  G_REGEX_ERROR_INVALID_DATA_CHARACTER = 164,
  G_REGEX_ERROR_EXTRA_SUBPATTERN_NAME = 165,
  G_REGEX_ERROR_BACKTRACKING_CONTROL_VERB_ARGUMENT_REQUIRED = 166,
  G_REGEX_ERROR_INVALID_CONTROL_CHAR = 168,
  G_REGEX_ERROR_MISSING_NAME = 169,
  G_REGEX_ERROR_NOT_SUPPORTED_IN_CLASS = 171,
  G_REGEX_ERROR_TOO_MANY_FORWARD_REFERENCES = 172,
  G_REGEX_ERROR_NAME_TOO_LONG = 175,
  G_REGEX_ERROR_CHARACTER_VALUE_TOO_LARGE = 176
}


define G_REGEX_ERROR g_regex_error_quark ()

g_regex_error_quark proto



.enum GRegexCompileFlags {
  G_REGEX_CASELESS          = 1 shl 0,
  G_REGEX_MULTILINE         = 1 shl 1,
  G_REGEX_DOTALL            = 1 shl 2,
  G_REGEX_EXTENDED          = 1 shl 3,
  G_REGEX_ANCHORED          = 1 shl 4,
  G_REGEX_DOLLAR_ENDONLY    = 1 shl 5,
  G_REGEX_UNGREEDY          = 1 shl 9,
  G_REGEX_RAW               = 1 shl 11,
  G_REGEX_NO_AUTO_CAPTURE   = 1 shl 12,
  G_REGEX_OPTIMIZE          = 1 shl 13,
  G_REGEX_FIRSTLINE         = 1 shl 18,
  G_REGEX_DUPNAMES          = 1 shl 19,
  G_REGEX_NEWLINE_CR        = 1 shl 20,
  G_REGEX_NEWLINE_LF        = 1 shl 21,
  G_REGEX_NEWLINE_CRLF      = G_REGEX_NEWLINE_CR or G_REGEX_NEWLINE_LF,
  G_REGEX_NEWLINE_ANYCRLF   = G_REGEX_NEWLINE_CR or 1 shl 22,
  G_REGEX_BSR_ANYCRLF       = 1 shl 23,
  G_REGEX_JAVASCRIPT_COMPAT = 1 shl 25
}



.enum GRegexMatchFlags {
  G_REGEX_MATCH_ANCHORED         = 1 shl 4,
  G_REGEX_MATCH_NOTBOL           = 1 shl 7,
  G_REGEX_MATCH_NOTEOL           = 1 shl 8,
  G_REGEX_MATCH_NOTEMPTY         = 1 shl 10,
  G_REGEX_MATCH_PARTIAL          = 1 shl 15,
  G_REGEX_MATCH_NEWLINE_CR       = 1 shl 20,
  G_REGEX_MATCH_NEWLINE_LF       = 1 shl 21,
  G_REGEX_MATCH_NEWLINE_CRLF     = G_REGEX_MATCH_NEWLINE_CR or G_REGEX_MATCH_NEWLINE_LF,
  G_REGEX_MATCH_NEWLINE_ANY      = 1 shl 22,
  G_REGEX_MATCH_NEWLINE_ANYCRLF  = G_REGEX_MATCH_NEWLINE_CR or G_REGEX_MATCH_NEWLINE_ANY,
  G_REGEX_MATCH_BSR_ANYCRLF      = 1 shl 23,
  G_REGEX_MATCH_BSR_ANY          = 1 shl 24,
  G_REGEX_MATCH_PARTIAL_SOFT     = G_REGEX_MATCH_PARTIAL,
  G_REGEX_MATCH_PARTIAL_HARD     = 1 shl 27,
  G_REGEX_MATCH_NOTEMPTY_ATSTART = 1 shl 28
}


;GRegex                  typedef _GRegex
;GMatchInfo              typedef _GMatchInfo

CALLBACK(GRegexEvalCallback, :ptr, :ptr, :gpointer)

g_regex_new proto :ptr, :GRegexCompileFlags, :GRegexMatchFlags, :ptr
g_regex_ref proto :ptr
g_regex_unref proto :ptr
g_regex_get_pattern proto :ptr
g_regex_get_max_backref proto :ptr
g_regex_get_capture_count proto :ptr
g_regex_get_has_cr_or_lf proto :ptr
g_regex_get_max_lookbehind proto :ptr
g_regex_get_string_number proto :ptr, :ptr
g_regex_escape_string proto :ptr, :gint
g_regex_escape_nul proto :ptr, :gint

g_regex_get_compile_flags proto :ptr
g_regex_get_match_flags proto :ptr


g_regex_match_simple proto :ptr, :ptr, :GRegexCompileFlags, :GRegexMatchFlags
g_regex_match proto :ptr, :ptr, :GRegexMatchFlags, :ptr
g_regex_match_full proto :ptr, :ptr, :gssize, :gint, :GRegexMatchFlags, :ptr, :ptr
g_regex_match_all proto :ptr, :ptr, :GRegexMatchFlags, :ptr
g_regex_match_all_full proto :ptr, :ptr, :gssize, :gint, :GRegexMatchFlags, :ptr, :ptr


g_regex_split_simple proto :ptr, :ptr, :GRegexCompileFlags, :GRegexMatchFlags
g_regex_split proto :ptr, :ptr, :GRegexMatchFlags
g_regex_split_full proto :ptr, :ptr, :gssize, :gint, :GRegexMatchFlags, :gint, :ptr


g_regex_replace proto :ptr, :ptr, :gssize, :gint, :ptr, :GRegexMatchFlags, :ptr
g_regex_replace_literal proto :ptr, :ptr, :gssize, :gint, :ptr, :GRegexMatchFlags, :ptr
g_regex_replace_eval proto :ptr, :ptr, :gssize, :gint, :GRegexMatchFlags, :GRegexEvalCallback, :gpointer, :ptr
g_regex_check_replacement proto :ptr, :ptr, :ptr


g_match_info_get_regex proto :ptr
g_match_info_get_string proto :ptr

g_match_info_ref proto :ptr
g_match_info_unref proto :ptr
g_match_info_free proto :ptr
g_match_info_next proto :ptr, :ptr
g_match_info_matches proto :ptr
g_match_info_get_match_count proto :ptr
g_match_info_is_partial_match proto :ptr
g_match_info_expand_references proto :ptr, :ptr, :ptr
g_match_info_fetch proto :ptr, :gint
g_match_info_fetch_pos proto :ptr, :gint, :ptr, :ptr
g_match_info_fetch_named proto :ptr, :ptr
g_match_info_fetch_named_pos proto :ptr, :ptr, :ptr, :ptr
g_match_info_fetch_all proto :ptr

endif
