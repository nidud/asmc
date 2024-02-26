; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

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
    mov     __a,[rcx]
    cmp     __a,[rdx]
    je      .0
    cmp     __a,'A'
    jb      .1
    cmp     __a,'Z'
    ja      .1
    or      al,0x20
    cmp     __a,[rdx]
    je      .0
    jmp     .2
.1:
    mov     __a,[rdx]
    cmp     __a,'A'
    jb      .2
    cmp     __a,'Z'
    ja      .2
    or      al,0x20
    cmp     __a,[rcx]
    je      .0
.2:
    mov     __a,[rcx]
    cmp     __a,[rdx]
    sbb     rax,rax
    sbb     rax,-1
.3:
    ret

_tcsicmp endp

    end
