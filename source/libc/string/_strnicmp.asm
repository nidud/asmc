; _STRNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_strnicmp proc uses rsi a:string_t, b:string_t, size:size_t

ifdef _WIN64
    mov     rsi,rcx
    mov     rcx,r8
else
    mov     esi,a
    mov     edx,b
    mov     ecx,size
endif
    dec     rsi
    dec     rdx
    mov     eax,1
.0:
    test    eax,eax
    jz      .2
    inc     rsi
    inc     rdx
    xor     eax,eax
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     al,[rsi]
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

_strnicmp endp

    end
