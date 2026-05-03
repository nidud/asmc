.pragma list(push, 0)

ifndef _LIBC_
include libc.inc
endif

LC_ALL		equ 0
LC_COLLATE	equ 1
LC_CTYPE	equ 2
LC_MONETARY	equ 3
LC_NUMERIC	equ 4
LC_TIME		equ 5

LC_MIN		equ LC_ALL
LC_MAX		equ LC_TIME

lconv		STRUC
decimal_point	LPSTR ?
thousands_sep	LPSTR ?
grouping	LPSTR ?
int_curr_symbol LPSTR ?
currency_symbol LPSTR ?
mon_decimal_point LPSTR ?
mon_thousands_sep LPSTR ?
mon_grouping	LPSTR ?
positive_sign	LPSTR ?
negative_sign	LPSTR ?
int_frac_digits BYTE ?
frac_digits	BYTE ?
p_cs_precedes	BYTE ?
p_sep_by_space	BYTE ?
n_cs_precedes	BYTE ?
n_sep_by_space	BYTE ?
p_sign_posn	BYTE ?
n_sign_posn	BYTE ?
lconv		ENDS
LPLCONV		typedef ptr lconv

ifndef _CONFIG_LOCALE_SWT
define _CONFIG_LOCALE_SWT
_ENABLE_PER_THREAD_LOCALE	    equ 0x1
_DISABLE_PER_THREAD_LOCALE	    equ 0x2
_ENABLE_PER_THREAD_LOCALE_GLOBAL    equ 0x10
_DISABLE_PER_THREAD_LOCALE_GLOBAL   equ 0x20
_ENABLE_PER_THREAD_LOCALE_NEW	    equ 0x100
_DISABLE_PER_THREAD_LOCALE_NEW	    equ 0x200
endif

_configthreadlocale	proto __cdecl :int_t
setlocale		proto __cdecl :int_t, :string_t
localeconv		proto __cdecl
_get_current_locale	proto __cdecl
_create_locale		proto __cdecl :int_t, :string_t

ifndef _locale_t
.template _locale_tstruct
    locinfo		ptr threadlocinfo ?
    mbcinfo		ptr threadmbcinfo ?
   .ends
   _locale_t		typedef ptr _locale_tstruct
endif
_free_locale		proto __cdecl :_locale_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
__get_current_locale	proto __cdecl
__create_locale		proto __cdecl :int_t, :string_t
__free_locale		proto __cdecl :_locale_t
endif

ifndef _WLOCALE_DEFINED
define _WLOCALE_DEFINED
_wsetlocale		proto __cdecl :int_t, :wstring_t
_wcreate_locale		proto __cdecl :int_t, :wstring_t
endif

.pragma list(pop)
