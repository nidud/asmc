
include string.inc
include internal_securecrt.inc

_FUNC_PROLOGUE  equ <>
_FUNC_NAME      equ <strcpy_s>
_CHAR           equ <char_t>
_DEST           equ <_Dst>
_SIZE           equ <_SizeInBytes>
_SRC            equ <_Src>

include tcscpy_s.inl
