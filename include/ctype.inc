.pragma list(push, 0)
ifndef __CTYPE_INC
__CTYPE_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
ifdef __PE__
option	dllimport:<msvcrt>
ifndef _MSVCRT
_MSVCRT equ <>
endif
endif

include crtdefs.inc

ifdef _CRTBLD
ifndef _CTYPE_DISABLE_MACROS
externdef __newclmap:uchar_t
externdef __newcumap:uchar_t
endif
externdef __ptlocinfo:pthreadlocinfo
externdef __ptmbcinfo:pthreadmbcinfo
externdef __globallocalestatus:int_t
externdef __locale_changed:int_t
externdef __initiallocinfo:threadlocinfo
externdef __initiallocalestructinfo:_locale_tstruct
__updatetlocinfo proto __cdecl
__updatetmbcinfo proto __cdecl
endif

_UPPER		equ 01h		; upper case letter
_LOWER		equ 02h		; lower case letter
_DIGIT		equ 04h		; digit[0-9]
_SPACE		equ 08h		; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h		; punctuation character
_CONTROL	equ 20h		; control character
_BLANK		equ 40h		; space char
_HEX		equ 80h		; hexadecimal digit

_LEADBYTE	equ 0x8000	; multibyte leadbyte
				; alphabetic character
_ALPHA		equ 0x0100 or _UPPER or _LOWER

externdef	_ctype:WORD	; Character type array
externdef	_pctype:LPWORD
externdef	_pwctype:LPWORD

isspace		proto __cdecl :SINT ; space, tab, carriage return, new line, vertical tab,
			    ; or formfeed (0x09 to 0x0D, 0x20)
isupper		proto __cdecl :SINT ; uppercase letter (A to Z)
isalpha		proto __cdecl :SINT ; letter (A to Z or a to z)
isalnum		proto __cdecl :SINT ; letter (A to Z or a to z) + digit (0 to 9)
isascii		proto __cdecl :SINT ; the low order byte of c is in the range 0 to 127
			    ; (0x00--0x7F)
iscntrl		proto __cdecl :SINT ; delete character or ordinary control character
			    ; (0x7F or 0x00 to 0x1F)
isdigit		proto __cdecl :SINT ; digit (0 to 9)
isgraph		proto __cdecl :SINT ; printing character, like isprint, except that
			    ; a space character is excluded
islower		proto __cdecl :SINT ; lowercase letter (a to z)
isprint		proto __cdecl :SINT ; printing character (0x20 to 0x7E)
ispunct		proto __cdecl :SINT ; punctuation character (iscntrl or isspace)
isxdigit	proto __cdecl :SINT ; hexadecimal digit (0 to 9, A to F, a to f)
toupper		proto __cdecl :SINT
tolower		proto __cdecl :SINT

_isctype	proto __cdecl :SINT, :SINT
_tolower	proto __cdecl :SINT
_toupper	proto __cdecl :SINT
__isascii	proto __cdecl :SINT
__toascii	proto __cdecl :SINT
__iscsymf	proto __cdecl :SINT
__iscsym	proto __cdecl :SINT

ifndef _WCTYPE_DEFINED
_WCTYPE_DEFINED equ <>

iswalpha	proto __cdecl :wint_t
iswupper	proto __cdecl :wint_t
iswlower	proto __cdecl :wint_t
iswdigit	proto __cdecl :wint_t
iswxdigit	proto __cdecl :wint_t
iswspace	proto __cdecl :wint_t
iswpunct	proto __cdecl :wint_t
iswalnum	proto __cdecl :wint_t
iswprint	proto __cdecl :wint_t
iswgraph	proto __cdecl :wint_t
iswcntrl	proto __cdecl :wint_t
iswascii	proto __cdecl :wint_t
isleadbyte	proto __cdecl :SINT
towupper	proto __cdecl :wchar_t
towlower	proto __cdecl :wchar_t
iswctype	proto __cdecl :wint_t, :wctype_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
isleadbyte	proto __cdecl :int_t
_isleadbyte_l	proto __cdecl :int_t, :_locale_t
is_wctype	proto __cdecl :wint_t, :wctype_t
endif
endif

endif
.pragma list(pop)

