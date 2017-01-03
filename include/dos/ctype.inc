ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_UPPER		equ 01h ; upper case letter
_LOWER		equ 02h ; lower case letter
_DIGIT		equ 04h ; digit[0-9]
_SPACE		equ 08h ; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h ; punctuation character
_CONTROL	equ 20h ; control character
_BLANK		equ 40h ; space char
_HEX		equ 80h ; hexadecimal digit


externdef	__ctype: BYTE	; 257
getctype	PROTO	; arg: AL, return AH

			; arg: AL, return ZF
isspace		PROTO	; space, tab, carriage return, new line, vertical tab,
			; or formfeed (0x09 to 0x0D, 0x20)
isupper		PROTO	; uppercase letter (A to Z)
islabel		PROTO	; lower | upper | digit | '_'

isalpha		PROTO	; letter (A to Z or a to z)
isascii		PROTO	; the low order byte of c is in the range 0 to 127
			; (0x00--0x7F)
iscntrl		PROTO	; delete character or ordinary control character
			; (0x7F or 0x00 to 0x1F)
isdigit		PROTO	; digit (0 to 9)
isprint		PROTO	; printing character
isgraph		PROTO	; printing character, like isprint, except that
			; a space character is excluded
islower		PROTO	; lowercase letter (a to z)
isprint		PROTO	; printing character (0x20 to 0x7E)
ispunct		PROTO	; punctuation character (iscntrl or isspace)
isxdigit	PROTO	; hexadecimal digit (0 to 9, A to F, a to f)

.list
