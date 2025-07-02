; _TCSCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname
    assume rdx:ptr tchar_t

_tcscat proc dst:tstring_t, src:tstring_t

    ldr     rcx,dst
    ldr     rdx,src
ifdef _WIN64
    mov     r8,rcx
endif
    xor     eax,eax
.0:
    cmp     _tal,[rcx]
    je      .1
    add     rcx,tchar_t
    jmp     .0
.1:
    mov     [rcx],[rdx]
    add     rcx,tchar_t
    add     rdx,tchar_t
    test    eax,eax
    jnz     .1
ifdef _WIN64
    mov     rax,r8
else
    mov     eax,dst
endif
    ret

_tcscat endp

    end
