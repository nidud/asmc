.pragma list(push, 0)
ifndef __CTYPE_INC
define __CTYPE_INC
ifndef __LIBC_INC
include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

ifndef WEOF
define WEOF 0xFFFF
endif

ifndef _CRT_CTYPEDATA_DEFINED
define _CRT_CTYPEDATA_DEFINED
__pctype_func	proto __cdecl
ifndef _M_CEE_PURE
externdef	_pctype:ptr ushort_t
else
define _pctype	<__pctype_func()>
endif
endif

define _UPPER		0x01
define _LOWER		0x02
define _DIGIT		0x04
define _SPACE		0x08
define _PUNCT		0x10
define _CONTROL		0x20
define _BLANK		0x40
define _HEX		0x80

define _LEADBYTE	0x8000
define _ALPHA		(0x0100 or _UPPER or _LOWER)

isspace		proto __cdecl :int_t
isupper		proto __cdecl :int_t
isalpha		proto __cdecl :int_t
isalnum		proto __cdecl :int_t
iscntrl		proto __cdecl :int_t
isdigit		proto __cdecl :int_t
isgraph		proto __cdecl :int_t
islower		proto __cdecl :int_t
isprint		proto __cdecl :int_t
ispunct		proto __cdecl :int_t
isxdigit	proto __cdecl :int_t
toupper		proto __cdecl :int_t
tolower		proto __cdecl :int_t
toascii		proto __cdecl :int_t

_tolower	proto __cdecl :int_t
_toupper	proto __cdecl :int_t

_isctype	proto __cdecl :int_t, :int_t
__isascii	proto __cdecl :int_t
__toascii	proto __cdecl :int_t
__iscsymf	proto __cdecl :int_t
__iscsym	proto __cdecl :int_t
isleadbyte	proto __cdecl :int_t

ifndef _WCTYPE_DEFINED
define _WCTYPE_DEFINED

iswalpha	proto __cdecl :int_t
iswupper	proto __cdecl :int_t
iswlower	proto __cdecl :int_t
iswdigit	proto __cdecl :int_t
iswxdigit	proto __cdecl :int_t
iswspace	proto __cdecl :int_t
iswpunct	proto __cdecl :int_t
iswalnum	proto __cdecl :int_t
iswprint	proto __cdecl :int_t
iswgraph	proto __cdecl :int_t
iswcntrl	proto __cdecl :int_t
iswascii	proto __cdecl :int_t
towupper	proto __cdecl :int_t
towlower	proto __cdecl :int_t
towascii	proto __cdecl :int_t
iswctype	proto __cdecl :wint_t, :wctype_t

_towlower	proto __cdecl :int_t
_towupper	proto __cdecl :int_t
__iswcsym	proto __cdecl :int_t
__iswcsymf	proto __cdecl :int_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
_isleadbyte_l	proto __cdecl :int_t, :_locale_t
is_wctype	proto __cdecl :wint_t, :wctype_t
endif
endif

ifdef _CRTBLD
externdef	_pcumap:string_t
externdef	_pclmap:string_t
endif
endif
.pragma list(pop)
