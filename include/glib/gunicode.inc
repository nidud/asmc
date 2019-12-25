ifndef __G_UNICODE_H__
__G_UNICODE_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc
include glib/gtypes.inc

gunichar   typedef guint32
gunichar2  typedef guint16

.enum GUnicodeType {
  G_UNICODE_CONTROL,
  G_UNICODE_FORMAT,
  G_UNICODE_UNASSIGNED,
  G_UNICODE_PRIVATE_USE,
  G_UNICODE_SURROGATE,
  G_UNICODE_LOWERCASE_LETTER,
  G_UNICODE_MODIFIER_LETTER,
  G_UNICODE_OTHER_LETTER,
  G_UNICODE_TITLECASE_LETTER,
  G_UNICODE_UPPERCASE_LETTER,
  G_UNICODE_SPACING_MARK,
  G_UNICODE_ENCLOSING_MARK,
  G_UNICODE_NON_SPACING_MARK,
  G_UNICODE_DECIMAL_NUMBER,
  G_UNICODE_LETTER_NUMBER,
  G_UNICODE_OTHER_NUMBER,
  G_UNICODE_CONNECT_PUNCTUATION,
  G_UNICODE_DASH_PUNCTUATION,
  G_UNICODE_CLOSE_PUNCTUATION,
  G_UNICODE_FINAL_PUNCTUATION,
  G_UNICODE_INITIAL_PUNCTUATION,
  G_UNICODE_OTHER_PUNCTUATION,
  G_UNICODE_OPEN_PUNCTUATION,
  G_UNICODE_CURRENCY_SYMBOL,
  G_UNICODE_MODIFIER_SYMBOL,
  G_UNICODE_MATH_SYMBOL,
  G_UNICODE_OTHER_SYMBOL,
  G_UNICODE_LINE_SEPARATOR,
  G_UNICODE_PARAGRAPH_SEPARATOR,
  G_UNICODE_SPACE_SEPARATOR
}

ifndef G_DISABLE_DEPRECATED
G_UNICODE_COMBINING_MARK equ G_UNICODE_SPACING_MARK
endif

.enum GUnicodeBreakType {
  G_UNICODE_BREAK_MANDATORY,
  G_UNICODE_BREAK_CARRIAGE_RETURN,
  G_UNICODE_BREAK_LINE_FEED,
  G_UNICODE_BREAK_COMBINING_MARK,
  G_UNICODE_BREAK_SURROGATE,
  G_UNICODE_BREAK_ZERO_WIDTH_SPACE,
  G_UNICODE_BREAK_INSEPARABLE,
  G_UNICODE_BREAK_NON_BREAKING_GLUE,
  G_UNICODE_BREAK_CONTINGENT,
  G_UNICODE_BREAK_SPACE,
  G_UNICODE_BREAK_AFTER,
  G_UNICODE_BREAK_BEFORE,
  G_UNICODE_BREAK_BEFORE_AND_AFTER,
  G_UNICODE_BREAK_HYPHEN,
  G_UNICODE_BREAK_NON_STARTER,
  G_UNICODE_BREAK_OPEN_PUNCTUATION,
  G_UNICODE_BREAK_CLOSE_PUNCTUATION,
  G_UNICODE_BREAK_QUOTATION,
  G_UNICODE_BREAK_EXCLAMATION,
  G_UNICODE_BREAK_IDEOGRAPHIC,
  G_UNICODE_BREAK_NUMERIC,
  G_UNICODE_BREAK_INFIX_SEPARATOR,
  G_UNICODE_BREAK_SYMBOL,
  G_UNICODE_BREAK_ALPHABETIC,
  G_UNICODE_BREAK_PREFIX,
  G_UNICODE_BREAK_POSTFIX,
  G_UNICODE_BREAK_COMPLEX_CONTEXT,
  G_UNICODE_BREAK_AMBIGUOUS,
  G_UNICODE_BREAK_UNKNOWN,
  G_UNICODE_BREAK_NEXT_LINE,
  G_UNICODE_BREAK_WORD_JOINER,
  G_UNICODE_BREAK_HANGUL_L_JAMO,
  G_UNICODE_BREAK_HANGUL_V_JAMO,
  G_UNICODE_BREAK_HANGUL_T_JAMO,
  G_UNICODE_BREAK_HANGUL_LV_SYLLABLE,
  G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE,
  G_UNICODE_BREAK_CLOSE_PARANTHESIS,
  G_UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER,
  G_UNICODE_BREAK_HEBREW_LETTER,
  G_UNICODE_BREAK_REGIONAL_INDICATOR
}

.enum GUnicodeScript {
  G_UNICODE_SCRIPT_INVALID_CODE = -1,
  G_UNICODE_SCRIPT_COMMON	= 0,
  G_UNICODE_SCRIPT_INHERITED,
  G_UNICODE_SCRIPT_ARABIC,
  G_UNICODE_SCRIPT_ARMENIAN,
  G_UNICODE_SCRIPT_BENGALI,
  G_UNICODE_SCRIPT_BOPOMOFO,
  G_UNICODE_SCRIPT_CHEROKEE,
  G_UNICODE_SCRIPT_COPTIC,
  G_UNICODE_SCRIPT_CYRILLIC,
  G_UNICODE_SCRIPT_DESERET,
  G_UNICODE_SCRIPT_DEVANAGARI,
  G_UNICODE_SCRIPT_ETHIOPIC,
  G_UNICODE_SCRIPT_GEORGIAN,
  G_UNICODE_SCRIPT_GOTHIC,
  G_UNICODE_SCRIPT_GREEK,
  G_UNICODE_SCRIPT_GUJARATI,
  G_UNICODE_SCRIPT_GURMUKHI,
  G_UNICODE_SCRIPT_HAN,
  G_UNICODE_SCRIPT_HANGUL,
  G_UNICODE_SCRIPT_HEBREW,
  G_UNICODE_SCRIPT_HIRAGANA,
  G_UNICODE_SCRIPT_KANNADA,
  G_UNICODE_SCRIPT_KATAKANA,
  G_UNICODE_SCRIPT_KHMER,
  G_UNICODE_SCRIPT_LAO,
  G_UNICODE_SCRIPT_LATIN,
  G_UNICODE_SCRIPT_MALAYALAM,
  G_UNICODE_SCRIPT_MONGOLIAN,
  G_UNICODE_SCRIPT_MYANMAR,
  G_UNICODE_SCRIPT_OGHAM,
  G_UNICODE_SCRIPT_OLD_ITALIC,
  G_UNICODE_SCRIPT_ORIYA,
  G_UNICODE_SCRIPT_RUNIC,
  G_UNICODE_SCRIPT_SINHALA,
  G_UNICODE_SCRIPT_SYRIAC,
  G_UNICODE_SCRIPT_TAMIL,
  G_UNICODE_SCRIPT_TELUGU,
  G_UNICODE_SCRIPT_THAANA,
  G_UNICODE_SCRIPT_THAI,
  G_UNICODE_SCRIPT_TIBETAN,
  G_UNICODE_SCRIPT_CANADIAN_ABORIGINAL,
  G_UNICODE_SCRIPT_YI,
  G_UNICODE_SCRIPT_TAGALOG,
  G_UNICODE_SCRIPT_HANUNOO,
  G_UNICODE_SCRIPT_BUHID,
  G_UNICODE_SCRIPT_TAGBANWA,

  G_UNICODE_SCRIPT_BRAILLE,
  G_UNICODE_SCRIPT_CYPRIOT,
  G_UNICODE_SCRIPT_LIMBU,
  G_UNICODE_SCRIPT_OSMANYA,
  G_UNICODE_SCRIPT_SHAVIAN,
  G_UNICODE_SCRIPT_LINEAR_B,
  G_UNICODE_SCRIPT_TAI_LE,
  G_UNICODE_SCRIPT_UGARITIC,

  G_UNICODE_SCRIPT_NEW_TAI_LUE,
  G_UNICODE_SCRIPT_BUGINESE,
  G_UNICODE_SCRIPT_GLAGOLITIC,
  G_UNICODE_SCRIPT_TIFINAGH,
  G_UNICODE_SCRIPT_SYLOTI_NAGRI,
  G_UNICODE_SCRIPT_OLD_PERSIAN,
  G_UNICODE_SCRIPT_KHAROSHTHI,

  G_UNICODE_SCRIPT_UNKNOWN,
  G_UNICODE_SCRIPT_BALINESE,
  G_UNICODE_SCRIPT_CUNEIFORM,
  G_UNICODE_SCRIPT_PHOENICIAN,
  G_UNICODE_SCRIPT_PHAGS_PA,
  G_UNICODE_SCRIPT_NKO,

  G_UNICODE_SCRIPT_KAYAH_LI,
  G_UNICODE_SCRIPT_LEPCHA,
  G_UNICODE_SCRIPT_REJANG,
  G_UNICODE_SCRIPT_SUNDANESE,
  G_UNICODE_SCRIPT_SAURASHTRA,
  G_UNICODE_SCRIPT_CHAM,
  G_UNICODE_SCRIPT_OL_CHIKI,
  G_UNICODE_SCRIPT_VAI,
  G_UNICODE_SCRIPT_CARIAN,
  G_UNICODE_SCRIPT_LYCIAN,
  G_UNICODE_SCRIPT_LYDIAN,

  G_UNICODE_SCRIPT_AVESTAN,
  G_UNICODE_SCRIPT_BAMUM,
  G_UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS,
  G_UNICODE_SCRIPT_IMPERIAL_ARAMAIC,
  G_UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI,
  G_UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN,
  G_UNICODE_SCRIPT_JAVANESE,
  G_UNICODE_SCRIPT_KAITHI,
  G_UNICODE_SCRIPT_LISU,
  G_UNICODE_SCRIPT_MEETEI_MAYEK,
  G_UNICODE_SCRIPT_OLD_SOUTH_ARABIAN,
  G_UNICODE_SCRIPT_OLD_TURKIC,
  G_UNICODE_SCRIPT_SAMARITAN,
  G_UNICODE_SCRIPT_TAI_THAM,
  G_UNICODE_SCRIPT_TAI_VIET,

  G_UNICODE_SCRIPT_BATAK,
  G_UNICODE_SCRIPT_BRAHMI,
  G_UNICODE_SCRIPT_MANDAIC,

  G_UNICODE_SCRIPT_CHAKMA,
  G_UNICODE_SCRIPT_MEROITIC_CURSIVE,
  G_UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS,
  G_UNICODE_SCRIPT_MIAO,
  G_UNICODE_SCRIPT_SHARADA,
  G_UNICODE_SCRIPT_SORA_SOMPENG,
  G_UNICODE_SCRIPT_TAKRI,

  G_UNICODE_SCRIPT_BASSA_VAH,
  G_UNICODE_SCRIPT_CAUCASIAN_ALBANIAN,
  G_UNICODE_SCRIPT_DUPLOYAN,
  G_UNICODE_SCRIPT_ELBASAN,
  G_UNICODE_SCRIPT_GRANTHA,
  G_UNICODE_SCRIPT_KHOJKI,
  G_UNICODE_SCRIPT_KHUDAWADI,
  G_UNICODE_SCRIPT_LINEAR_A,
  G_UNICODE_SCRIPT_MAHAJANI,
  G_UNICODE_SCRIPT_MANICHAEAN,
  G_UNICODE_SCRIPT_MENDE_KIKAKUI,
  G_UNICODE_SCRIPT_MODI,
  G_UNICODE_SCRIPT_MRO,
  G_UNICODE_SCRIPT_NABATAEAN,
  G_UNICODE_SCRIPT_OLD_NORTH_ARABIAN,
  G_UNICODE_SCRIPT_OLD_PERMIC,
  G_UNICODE_SCRIPT_PAHAWH_HMONG,
  G_UNICODE_SCRIPT_PALMYRENE,
  G_UNICODE_SCRIPT_PAU_CIN_HAU,
  G_UNICODE_SCRIPT_PSALTER_PAHLAVI,
  G_UNICODE_SCRIPT_SIDDHAM,
  G_UNICODE_SCRIPT_TIRHUTA,
  G_UNICODE_SCRIPT_WARANG_CITI,

  G_UNICODE_SCRIPT_AHOM,
  G_UNICODE_SCRIPT_ANATOLIAN_HIEROGLYPHS,
  G_UNICODE_SCRIPT_HATRAN,
  G_UNICODE_SCRIPT_MULTANI,
  G_UNICODE_SCRIPT_OLD_HUNGARIAN,
  G_UNICODE_SCRIPT_SIGNWRITING
}

;guint32
g_unicode_script_to_iso15924 proto __cdecl \
		script: GUnicodeScript

;GUnicodeScript
g_unicode_script_from_iso15924 proto __cdecl \
	      iso15924: guint32


;gboolean
g_unichar_isalnum proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isalpha proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_iscntrl proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isdigit proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isgraph proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_islower proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isprint proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_ispunct proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isspace proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isupper proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isxdigit proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_istitle proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_isdefined proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_iswide proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_iswide_cjk proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_iszerowidth proto __cdecl \
		     c: gunichar

;gboolean
g_unichar_ismark proto __cdecl \
		     c: gunichar


;gunichar
g_unichar_toupper proto __cdecl \
		     c: gunichar

;gunichar
g_unichar_tolower proto __cdecl \
		     c: gunichar

;gunichar
g_unichar_totitle proto __cdecl \
		     c: gunichar


;gint
g_unichar_digit_value proto __cdecl \
		     c: gunichar


;gint
g_unichar_xdigit_value proto __cdecl \
		     c: gunichar


;GUnicodeType
g_unichar_type proto __cdecl \
		     c: gunichar


;GUnicodeBreakType
g_unichar_break_type proto __cdecl \
		     c: gunichar


;gint
g_unichar_combining_class proto __cdecl \
		    uc: gunichar


;gboolean
g_unichar_get_mirror_char proto __cdecl \
		   _ch: gunichar,
	   mirrored_ch: ptr gunichar


;GUnicodeScript
g_unichar_get_script proto __cdecl \
		   _ch: gunichar

;gboolean
g_unichar_validate proto __cdecl \
		   _ch: gunichar

;gboolean
g_unichar_compose proto __cdecl \
		     a: gunichar,
		     b: gunichar,
		   _ch: ptr gunichar

;gboolean
g_unichar_decompose proto __cdecl \
		   _ch: gunichar,
		     a: ptr gunichar,
		     b: ptr gunichar

;gsize
g_unichar_fully_decompose proto __cdecl \
		   _ch: gunichar,
		compat: gboolean,
		result: ptr gunichar,
	    result_len: gsize


G_UNICHAR_MAX_DECOMPOSITION_LENGTH equ 18

;void
g_unicode_canonical_ordering proto __cdecl \
		string: ptr gunichar,
		   len: gsize



;GLIB_VAR gchar * g_utf8_skip;

g_utf8_next_char macro p
	exitm<.err>
	endm

;gunichar
g_utf8_get_char proto __cdecl \
		     p: ptr gchar

;gunichar
g_utf8_get_char_validated proto __cdecl \
		     p: ptr gchar,
	       max_len: gssize

;gchar*
g_utf8_offset_to_pointer proto __cdecl \
		  _str: ptr gchar,
	       _offset: glong

;glong
g_utf8_pointer_to_offset proto __cdecl \
		  _str: ptr gchar,
		   pos: ptr gchar

;gchar*
g_utf8_prev_char proto __cdecl \
		     p: ptr gchar

;gchar*
g_utf8_find_next_char proto __cdecl \
		     p: ptr gchar,
		  _end: ptr gchar

;gchar*
g_utf8_find_prev_char proto __cdecl \
		  _str: ptr gchar,
		     p: ptr gchar

;glong
g_utf8_strlen proto __cdecl \
		     p: ptr gchar,
		   max: gssize

;gchar
g_utf8_substring proto __cdecl \
		  _str: ptr gchar,
	     start_pos: glong,
	       end_pos: glong

;gchar
g_utf8_strncpy proto __cdecl \
		  dest: ptr gchar,
		   src: ptr gchar,
		     n: gsize


;gchar*
g_utf8_strchr proto __cdecl \
		     p: ptr gchar,
		   len: gssize,
		     c: gunichar

;gchar*
g_utf8_strrchr proto __cdecl \
		     p: ptr gchar,
		   len: gssize,
		     c: gunichar

;gchar*
g_utf8_strreverse proto __cdecl \
		  _str: ptr gchar,
		   len: gssize


;gunichar2
g_utf8_to_utf16 proto __cdecl \
		  _str: ptr gchar,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gunichar
g_utf8_to_ucs4 proto __cdecl \
		  _str: ptr gchar,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gunichar
g_utf8_to_ucs4_fast proto __cdecl \
		  _str: ptr gchar,
		   len: glong,
	 items_written: ptr glong

;gunichar
g_utf16_to_ucs4 proto __cdecl \
		  _str: ptr gunichar2,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gchar*
g_utf16_to_utf8 proto __cdecl \
		  _str: ptr gunichar2,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gunichar2
g_ucs4_to_utf16 proto __cdecl \
		  _str: ptr gunichar,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gchar*
g_ucs4_to_utf8 proto __cdecl \
		  _str: ptr gunichar,
		   len: glong,
	    items_read: ptr glong,
	 items_written: ptr glong,
		 error: ptr GError

;gint
g_unichar_to_utf8 proto __cdecl \
		     c: gunichar,
		outbuf: ptr gchar

;gboolean
g_utf8_validate proto __cdecl \
		  _str: ptr gchar,
	       max_len: gssize,
		  _end: ptr gchar
;gchar
g_utf8_strup proto __cdecl \
		  _str: ptr gchar,
		   len: gssize

;gchar
g_utf8_strdown proto __cdecl \
		  _str: ptr gchar,
		   len: gssize
;gchar
g_utf8_casefold proto __cdecl \
		  _str: ptr gchar,
		   len: gssize

.enum GNormalizeMode {
  G_NORMALIZE_DEFAULT,
  G_NORMALIZE_NFD = G_NORMALIZE_DEFAULT,
  G_NORMALIZE_DEFAULT_COMPOSE,
  G_NORMALIZE_NFC = G_NORMALIZE_DEFAULT_COMPOSE,
  G_NORMALIZE_ALL,
  G_NORMALIZE_NFKD = G_NORMALIZE_ALL,
  G_NORMALIZE_ALL_COMPOSE,
  G_NORMALIZE_NFKC = G_NORMALIZE_ALL_COMPOSE
}

;gchar
g_utf8_normalize proto __cdecl \
		  _str: ptr gchar,
		   len: gssize,
		  mode: GNormalizeMode

;gint
g_utf8_collate proto __cdecl \
		  str1: ptr gchar,
		  str2: ptr gchar
;gchar
g_utf8_collate_key proto __cdecl \
		  _str: ptr gchar,
		   len: gssize
;gchar
g_utf8_collate_key_for_filename proto __cdecl \
		  _str: ptr gchar,
		   len: gssize


_g_utf8_make_valid proto __cdecl :ptr gchar

endif
