ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_LABEL		equ 01h		; _UPPER + _LOWER + _DIGIT + '@' + '_' + '$' + '?'
_DOT		equ 02h		; '.'
_DIGIT		equ 04h		; digit[0-9]
_SPACE		equ 08h		; tab, carriage return, newline, vertical tab or form feed
_PUNCT		equ 10h		; punctuation character
_CONTROL	equ 20h		; control character
_BLANK		equ 40h		; space char
_HEX		equ 80h		; hexadecimal digit

externdef	__ltype: BYTE	; Label type array

islabel		PROTO :DWORD
islabel0	PROTO :DWORD, :DWORD
strlabel	PROTO :LPSTR, :UINT

.list
