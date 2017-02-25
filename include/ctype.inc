ifndef __LIBC_INC
 include libc.inc
endif

.xlist
IFDEF __PE__
option		dllimport:<msvcrt>
ENDIF

_UPPER		equ 01h		; upper case letter
_LOWER		equ 02h		; lower case letter
_DIGIT		equ 04h		; digit[0-9]
_SPACE		equ 08h		; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h		; punctuation character
_CONTROL	equ 20h		; control character
_BLANK		equ 40h		; space char
_HEX		equ 80h		; hexadecimal digit

_LEADBYTE	equ 0x8000	; multibyte leadbyte
_ALPHA		equ 0x0100 or _UPPER or _LOWER ; alphabetic character

externdef	_ctype:WORD	; Character type array
externdef	_pctype:LPWORD
externdef	_pwctype:LPWORD

isspace		PROTO :SINT	; space, tab, carriage return, new line, vertical tab,
				; or formfeed (0x09 to 0x0D, 0x20)
isupper		PROTO :SINT	; uppercase letter (A to Z)
isalpha		PROTO :SINT	; letter (A to Z or a to z)
isalnum		PROTO :SINT	; letter (A to Z or a to z) + digit (0 to 9)
isascii		PROTO :SINT	; the low order byte of c is in the range 0 to 127
				; (0x00--0x7F)
iscntrl		PROTO :SINT	; delete character or ordinary control character
				; (0x7F or 0x00 to 0x1F)
isdigit		PROTO :SINT	; digit (0 to 9)
isgraph		PROTO :SINT	; printing character, like isprint, except that
				; a space character is excluded
islower		PROTO :SINT	; lowercase letter (a to z)
isprint		PROTO :SINT	; printing character (0x20 to 0x7E)
ispunct		PROTO :SINT	; punctuation character (iscntrl or isspace)
isxdigit	PROTO :SINT	; hexadecimal digit (0 to 9, A to F, a to f)
toupper		PROTO :SINT
tolower		PROTO :SINT

_isctype	PROTO :SINT, :SINT
_tolower	PROTO :SINT
_toupper	PROTO :SINT
__isascii	PROTO :SINT
__toascii	PROTO :SINT
__iscsymf	PROTO :SINT
__iscsym	PROTO :SINT

ifndef _WCTYPE_DEFINED

iswalpha	proto :wint_t
iswupper	proto :wint_t
iswlower	proto :wint_t
iswdigit	proto :wint_t
iswxdigit	proto :wint_t
iswspace	proto :wint_t
iswpunct	proto :wint_t
iswalnum	proto :wint_t
iswprint	proto :wint_t
iswgraph	proto :wint_t
iswcntrl	proto :wint_t
iswascii	proto :wint_t
isleadbyte	proto :SINT

towupper	proto :wchar_t
towlower	proto :wchar_t

iswctype	proto :wint_t, :wctype_t

_WCTYPE_DEFINED equ 1
endif

.list
