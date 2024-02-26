; _TSTRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcscmp proc a:LPTSTR, b:LPTSTR

    ldr     rcx,a
    ldr     rdx,b
    xor     eax,eax
.0:
    xor     __a,[rcx]
    jz      .5
    sub     __a,[rdx]
    jnz     .1
    xor     __a,[rcx+1*TCHAR]
    jz      .4
    sub     __a,[rdx+1*TCHAR]
    jnz     .1
    xor     __a,[rcx+2*TCHAR]
    jz      .3
    sub     __a,[rdx+2*TCHAR]
    jnz     .1
    xor     __a,[rcx+3*TCHAR]
    jz      .2
    sub     __a,[rdx+3*TCHAR]
    jnz     .1
    add     rcx,4*TCHAR
    add     rdx,4*TCHAR
    jmp     .0
.1:
    sbb     rax,rax
    sbb     rax,-1
    jmp     .6
.2:
    add     rdx,TCHAR
.3:
    add     rdx,TCHAR
.4:
    add     rdx,TCHAR
.5:
    sub     __a,[rdx]
    jnz     .1
.6:
    ret

_tcscmp endp

    end
