.pragma list(push, 0)

include locale.inc

ERR_BUFFER_TOO_SMALL	equ 1	; should be in windef.h

_CLOCALEHANDLE		equ 0	; "C" locale handle
_CLOCALECP		equ CP_ACP ; "C" locale Code page


_MAX_WDAY_ABBR		equ 4
_MAX_WDAY		equ 10
_MAX_MONTH_ABBR		equ 4
_MAX_MONTH		equ 10
_MAX_AMPM		equ 3

_DATE_LENGTH		equ 8	; mm/dd/yy (null not included)
_TIME_LENGTH		equ 8	; hh:mm:ss (null not included)


__lc_time_data		STRUC
wday_abbr		LPSTR  7 dup(?)
wday			LPSTR  7 dup(?)
month_abbr		LPSTR 12 dup(?)
month			LPSTR 12 dup(?)
ampm			LPSTR  2 dup(?)
ww_sdatefmt		LPSTR ?
ww_ldatefmt		LPSTR ?
ww_timefmt		LPSTR ?
__lc_time_data		ENDS


MAX_LANG_LEN		equ 64	; max language name length
MAX_CTRY_LEN		equ 64	; max country name length
MAX_MODIFIER_LEN	equ 0	; max modifier name length - n/a
MAX_LC_LEN		equ MAX_LANG_LEN + MAX_CTRY_LEN + MAX_MODIFIER_LEN + 3
MAX_CP_LEN		equ 8	; max code page name length
CATNAMES_LEN		equ 57	; "LC_COLLATE=;LC_CTYPE=;..." length

LC_INT_TYPE		equ 0
LC_STR_TYPE		equ 1

LC_ID			STRUCT
wLanguage		dw ?
wCountry		dw ?
wCodePage		dw ?
LC_ID			ENDS
LPLC_ID			TYPEDEF PTR LC_ID

LC_STRINGS		STRUC
szLanguage		db MAX_LANG_LEN dup(?)
szCountry		db MAX_CTRY_LEN dup(?)
szCodePage		db MAX_CP_LEN dup(?)
LC_STRINGS		ENDS
LPLC_STRINGS		TYPEDEF PTR LC_STRINGS

externdef		__lc_id:LC_ID		; complete info from GetQualifiedLocale
externdef		__lc_handle:UINT	; LCID- locale "handles" -- ignores country info
externdef		__lc_codepage:UINT	; code page
externdef		__lc_collate_cp:UINT	; code page for LC_COLLATE

__get_qualified_locale	PROTO :LPLC_STRINGS, :LPLC_ID, :LPLC_STRINGS
;__getlocaleinfo		PROTO :SINT, :LCID, :LCTYPE, :PVOID

externdef		__lconv_c:lconv
externdef		__lconv: ptr lconv
externdef		__lconv_static_decimal:SBYTE
externdef		__lconv_static_null:SBYTE


__init_collate		PROTO
__init_ctype		PROTO
__init_monetary		PROTO
__init_numeric		PROTO
__init_time		PROTO
__init_dummy		PROTO

.pragma list(pop)
