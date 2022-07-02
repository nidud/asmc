; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_memicmp proc a:ptr, b:ptr, size:size_t
ifndef _WIN64
    push    ebx
    mov     ecx,a
    mov     edx,b
    mov     ebx,size
endif
    dec     rcx
    dec     rdx
.0:
ifdef _WIN64
    test    r8d,r8d
    jz      .2
    dec     r8d
else
    test    ebx,ebx
    jz      .2
    dec     ebx
endif
    inc     rdx
    inc     rcx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .0
    xor     al,0x20
    cmp     al,'A'
    jb      .1
    cmp     al,'z'
    ja      .1
    cmp     al,0x60
    je      .1
    cmp     al,[rdx]
    je      .0
.1:
    xor     al,0x20
    cmp     al,[rdx]
ifdef _WIN64
    sbb     r8,r8
    sbb     r8,-1
.2:
    mov     rax,r8
else
    sbb     ebx,ebx
    sbb     ebx,-1
.2:
    mov     eax,ebx
    pop     ebx
endif
    ret

_memicmp endp

    end
