ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_UPPER		equ 01h		; upper case letter
_LOWER		equ 02h		; lower case letter
_DIGIT		equ 04h		; digit[0-9]
_SPACE		equ 08h		; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h		; punctuation character
_CONTROL	equ 20h		; control character
_BLANK		equ 40h		; space char
_HEX		equ 80h		; hexadecimal digit

externdef	__ctype: SBYTE	; Character type array

isspace		PROTO :SIZE_T	; space, tab, carriage return, new line, vertical tab,
				; or formfeed (0x09 to 0x0D, 0x20)
isupper		PROTO :SIZE_T	; uppercase letter (A to Z)
isalpha		PROTO :SIZE_T	; letter (A to Z or a to z)
isalnum		PROTO :SIZE_T	; letter (A to Z or a to z) + digit (0 to 9)
isascii		PROTO :SIZE_T	; the low order byte of c is in the range 0 to 127
				; (0x00--0x7F)
iscntrl		PROTO :SIZE_T	; delete character or ordinary control character
				; (0x7F or 0x00 to 0x1F)
isdigit		PROTO :SIZE_T	; digit (0 to 9)
isgraph		PROTO :SIZE_T	; printing character, like isprint, except that
				; a space character is excluded
islower		PROTO :SIZE_T	; lowercase letter (a to z)
isprint		PROTO :SIZE_T	; printing character (0x20 to 0x7E)
ispunct		PROTO :SIZE_T	; punctuation character (iscntrl or isspace)
isxdigit	PROTO :SIZE_T	; hexadecimal digit (0 to 9, A to F, a to f)
toupper		PROTO :SIZE_T
tolower		PROTO :SIZE_T

.list
