
include string.inc
include internal_securecrt.inc

_FUNC_PROLOGUE  equ <>
_FUNC_NAME      equ <strcat_s>
_CHAR           equ <char_t>
_DEST           equ <_Dst>
_SIZE           equ <_SizeInWords>
_SRC            equ <_Src>

include tcscat_s.inl

