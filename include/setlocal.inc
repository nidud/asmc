.pragma list(push, 0)

include locale.inc

ERR_BUFFER_TOO_SMALL	equ 1	; should be in windef.h

CP_ACP			equ 0	; default to ANSI code page
_CLOCALEHANDLE		equ 0	; "C" locale handle
_CLOCALECP		equ CP_ACP ; "C" locale Code page
_COFFSET		equ 127

_PER_THREAD_LOCALE_BIT	equ 0x2
_GLOBAL_LOCALE_BIT	equ 0x1

_MAX_WDAY_ABBR		equ 4
_MAX_WDAY		equ 10
_MAX_MONTH_ABBR		equ 4
_MAX_MONTH		equ 10
_MAX_AMPM		equ 3

_DATE_LENGTH		equ 8	; mm/dd/yy (null not included)
_TIME_LENGTH		equ 8	; hh:mm:ss (null not included)


ifndef __LC_TIME_DATA
define __LC_TIME_DATA
__lc_time_data		STRUC
wday_abbr		LPSTR  7 dup(?)
wday			LPSTR  7 dup(?)
month_abbr		LPSTR 12 dup(?)
month			LPSTR 12 dup(?)
ampm			LPSTR  2 dup(?)
ww_sdatefmt		LPSTR ?
ww_ldatefmt		LPSTR ?
ww_timefmt		LPSTR ?
ww_caltype		SINT ?
refcount		SINT ?
_W_wday_abbr		LPWSTR	7 dup(?)
_W_wday			LPWSTR	7 dup(?)
_W_month_abbr		LPWSTR 12 dup(?)
_W_month		LPWSTR 12 dup(?)
_W_ampm			LPWSTR	2 dup(?)
_W_ww_sdatefmt		LPWSTR ?
_W_ww_ldatefmt		LPWSTR ?
_W_ww_timefmt		LPWSTR ?
_W_ww_locale_name	LPWSTR ?
__lc_time_data		ENDS
endif

MAX_LANG_LEN		equ 64
MAX_CTRY_LEN		equ 64
MAX_MODIFIER_LEN	equ 0
MAX_LC_LEN		equ MAX_LANG_LEN + MAX_CTRY_LEN + MAX_MODIFIER_LEN + 3
MAX_CP_LEN		equ 16
CATNAMES_LEN		equ 57

LC_INT_TYPE		equ 0
LC_STR_TYPE		equ 1
LC_WSTR_TYPE		equ 2

ifndef _SETLOC_STRUCT_DEFINED
define _SETLOC_STRUCT_DEFINED

_is_ctype_compatible	STRUC
id			dd ?
is_clike		SINT ?
_is_ctype_compatible	ENDS

_setloc_struct		STRUC
pchLanguage		LPWSTR ?
pchCountry		LPWSTR ?
iLocState		SINT ?
iPrimaryLen		SINT ?
bAbbrevLanguage		BOOL ?
bAbbrevCountry		BOOL ?
_cachecp		UINT ?
_cachein		wchar_t MAX_LC_LEN dup(?)
_cacheout		wchar_t MAX_LC_LEN dup(?)
_Loc_c			_is_ctype_compatible 5 dup(<>)
_cacheLocaleName	wchar_t LOCALE_NAME_MAX_LENGTH dup(?)
_setloc_struct		ENDS
_psetloc_struct		typedef ptr _setloc_struct

_setloc_downlevel_struct STRUC
iLcidState		SINT ?
lcidLanguage		LCID ?
lcidCountry		LCID ?
_setloc_downlevel_struct ENDS
_psetloc_downlevel_struct typedef ptr _setloc_downlevel_struct
endif

include threadlocinfo.inc

LC_STRINGS		STRUCT
szLanguage		wchar_t MAX_LANG_LEN dup(?)
szCountry		wchar_t MAX_CTRY_LEN dup(?)
szCodePage		wchar_t MAX_CP_LEN dup(?)
szLocaleName		wchar_t LOCALE_NAME_MAX_LENGTH dup(?)
LC_STRINGS		ENDS
LPLC_STRINGS		typedef ptr LC_STRINGS

;;  local structure definitions
LOCALETAB		STRUC
szName			LPWSTR ?
chAbbrev		wchar_t 4 dup(?)
LOCALETAB		ENDS

externdef		__ptlocinfo:pthreadlocinfo
__updatetlocinfo	proto __cdecl
_setptlocale		proto __cdecl :int_t

ifndef _M_CEE_PURE
externdef		__lconv:ptr lconv ;; pointer to current lconv structure
endif

;; These functions are for enabling STATIC_CPPLIB functionality
___lc_locale_name_func	proto __cdecl
___lc_codepage_func	proto __cdecl
___lc_collate_cp_func	proto __cdecl

ifndef LCTYPE
LCTYPE			typedef DWORD
endif

__get_qualified_locale	proto __cdecl :LPLC_STRINGS, :ptr UINT, :LPLC_STRINGS
__get_qualified_locale_downlevel proto __cdecl :LPLC_STRINGS, :ptr UINT, :LPLC_STRINGS
__getlocaleinfo		proto __cdecl :_locale_t, :int_t, :LPCWSTR, :LCTYPE, :ptr

;; lconv structure for the "C" locale
externdef __lconv_c:lconv

;; Initialization functions for locale categories

__init_collate		proto __cdecl :ptr threadlocinfo
__init_ctype		proto __cdecl :ptr threadlocinfo
__init_monetary		proto __cdecl :ptr threadlocinfo
__init_numeric		proto __cdecl :ptr threadlocinfo
__init_time		proto __cdecl :ptr threadlocinfo
__init_dummy		proto __cdecl :ptr threadlocinfo

.class _LocaleUpdate ;:_locale_t

    localeinfo	_locale_tstruct <>
    ptd		_ptiddata ?
    updated	BOOL ?

    GetLocaleT	proc
   .ends

.pragma list(pop)
