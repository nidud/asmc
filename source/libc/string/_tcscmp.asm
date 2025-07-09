; _TCSCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcscmp proc a:tstring_t, b:tstring_t

    ldr     rcx,a
    ldr     rdx,b

    mov     eax,1
.0:
    test    eax,eax
    jz      .1
    mov     _tal,[rcx]
    cmp     _tal,[rdx]
    lea     rcx,[rcx+tchar_t]
    lea     rdx,[rdx+tchar_t]
    je      .0
    sbb     rax,rax
    sbb     rax,-1
.1:
    ret

_tcscmp endp

    end
