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
_LABEL		equ 40h		; _UPPER + _LOWER + _DIGIT + '@' + '_' + '$' + '?'
_HEX		equ 80h		; hexadecimal digit

externdef	_ltype: BYTE	; Label type array

.list
