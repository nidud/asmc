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
    xor     eax,eax
.0:
    xor     _tal,[rcx]
    jz      .5
    sub     _tal,[rdx]
    jnz     .1
    xor     _tal,[rcx+1*tchar_t]
    jz      .4
    sub     _tal,[rdx+1*tchar_t]
    jnz     .1
    xor     _tal,[rcx+2*tchar_t]
    jz      .3
    sub     _tal,[rdx+2*tchar_t]
    jnz     .1
    xor     _tal,[rcx+3*tchar_t]
    jz      .2
    sub     _tal,[rdx+3*tchar_t]
    jnz     .1
    add     rcx,4*tchar_t
    add     rdx,4*tchar_t
    jmp     .0
.1:
    sbb     rax,rax
    sbb     rax,-1
    jmp     .6
.2:
    add     rdx,tchar_t
.3:
    add     rdx,tchar_t
.4:
    add     rdx,tchar_t
.5:
    sub     _tal,[rdx]
    jnz     .1
.6:
    ret

_tcscmp endp

    end
