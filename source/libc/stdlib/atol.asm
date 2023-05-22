; ATOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

    option dotname

atol proc string:string_t

    ldr     rcx,string

    xor     edx,edx
    xor     eax,eax
.0:
    mov     dl,[rcx]
    inc     rcx
    cmp     dl,' '
    je      .0
ifdef _WIN64
    mov     r8b,dl
else
    push    edx
endif
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
    imul    eax,eax,10
    add     eax,edx
    mov     dl,[rcx]
    inc     rcx
    jmp     .2
.3:
ifdef _WIN64
    cmp     r8b,'-'
else
    pop     ecx
    cmp     cl,'-'
endif
    jne     .4
    neg     eax
.4:
    ret

atol endp

    end
