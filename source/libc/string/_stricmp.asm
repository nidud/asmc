; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_stricmp proc a:string_t, b:string_t
ifndef _WIN64
    mov     ecx,a
    mov     edx,b
endif
    dec     rcx
    dec     rdx
    mov     eax,1
.0:
    test    eax,eax
    jz      .2
    inc     rcx
    inc     rdx
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
    sbb     rax,rax
    sbb     rax,-1
.2:
    ret

_stricmp endp

    end
