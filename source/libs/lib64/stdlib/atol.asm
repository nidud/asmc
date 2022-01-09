; ATOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

    option dotname

atol proc string:string_t

    xor     edx,edx
    xor     eax,eax
.0:
    mov     dl,[rcx]
    inc     rcx
    cmp     dl,' '
    je      .0
    mov     r8b,dl
    cmp     dl,'+'
    je      .1
    cmp     dl,'-'
    jne     .2
.1:
    mov     dl,[rcx]
    inc     rcx
.2:
    sub     dl,'0'
    jb      .3
    cmp     dl,9
    ja      .3
    imul    rax,rax,10
    add     rax,rdx
    mov     dl,[rcx]
    inc     rcx
    jmp     .2
.3:
    cmp     r8b,'-'
    jne     .4
    neg     rax
.4:
    ret

atol endp

    end
