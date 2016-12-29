ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_ST_SIGN	equ 0x0001
_ST_NEGNUM	equ 0x0002
_ST_NEGEXP	equ 0x0004
_ST_ISZERO	equ 0x0008
_ST_ISHEX	equ 0x0010
_ST_ISNAN	equ 0x0020
_ST_ISINF	equ 0x0040
_ST_INVALID	equ 0x0080
_ST_UNDERFLOW	equ 0x0100
_ST_OVERFLOW	equ 0x0200
_ST_DIGITS	equ 0x0400
_ST_DOT		equ 0x0800

S_STRFLT	STRUC
flags		dd ?	; parsing flags
exponent	dd ?	; exponent of floating point number
string		LPSTR ? ; pointer to buffer or string
mantissa	PVOID ? ; pointer to mantissa
S_STRFLT	ENDS

_strtoflt	PROTO :LPSTR

.list
