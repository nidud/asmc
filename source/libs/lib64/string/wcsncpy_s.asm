; WCSNCPY_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include internal_securecrt.inc

_FUNC_PROLOGUE  equ <>
_FUNC_NAME      equ <wcsncpy_s>
_CHAR           equ <wchar_t>
_DEST           equ <_Dst>
_SIZE           equ <_SizeInWords>
_SRC            equ <_Src>
_COUNT          equ <_Count>

include tcsncpy_s.inl

    end
