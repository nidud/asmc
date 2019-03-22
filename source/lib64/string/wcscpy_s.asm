
include string.inc
include internal_securecrt.inc

_FUNC_PROLOGUE  equ <>
_FUNC_NAME      equ <wcscpy_s>
_CHAR           equ <wchar_t>
_DEST           equ <_Dst>
_SIZE           equ <_SizeInWords>
_SRC            equ <_Src>

include tcscpy_s.inl
