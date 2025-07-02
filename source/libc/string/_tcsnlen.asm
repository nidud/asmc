; _TCSNLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; size_t strnlen(const char *str, size_t maxsize);
; size_t wcsnlen(const wchar_t *str, size_t maxsize);
;
include string.inc
include tchar.inc

.code

_tcsnlen proc string:tstring_t, maxsize:size_t

    ldr rcx,string
    ldr rdx,maxsize

    ; Note that we do not check if string == NULL, because we do not
    ; return errno_t...

    .for ( eax = 0 : rax < rdx && tchar_t ptr [rcx] : rax++, rcx += tchar_t )
    .endf
    ret

_tcsnlen endp

    end
