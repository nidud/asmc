; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcsicmp proc a:LPTSTR, b:LPTSTR

    ldr     rcx,a
    ldr     rdx,b

    sub     rcx,TCHAR
    sub     rdx,TCHAR
    mov     eax,1
.0:
    test    eax,eax
    jz      .3
    add     rcx,TCHAR
    add     rdx,TCHAR
    mov     _tal,[rcx]
    cmp     _tal,[rdx]
    je      .0
    cmp     _tal,'A'
    jb      .1
    cmp     _tal,'Z'
    ja      .1
    or      al,0x20
    cmp     _tal,[rdx]
    je      .0
    jmp     .2
.1:
    mov     _tal,[rdx]
    cmp     _tal,'A'
    jb      .2
    cmp     _tal,'Z'
    ja      .2
    or      al,0x20
    cmp     _tal,[rcx]
    je      .0
.2:
    mov     _tal,[rcx]
    cmp     _tal,[rdx]
    sbb     rax,rax
    sbb     rax,-1
.3:
    ret

_tcsicmp endp

    end
