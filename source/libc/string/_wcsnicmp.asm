; _WCSNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_wcsnicmp proc uses rsi a:wstring_t, b:wstring_t, count:size_t

    ldr     rsi,a
    ldr     rdx,b
    ldr     rcx,count

    sub     rsi,2
    sub     rdx,2
    mov     eax,1
.0:
    test    eax,eax
    jz      .2
    add     rsi,2
    add     rdx,2
    xor     eax,eax
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     ax,[rsi]
    cmp     ax,[rdx]
    je      .0
    xor     al,0x20
    cmp     ax,'A'
    jb      .1
    cmp     ax,'z'
    ja      .1
    cmp     ax,0x60
    je      .1
    cmp     ax,[rdx]
    je      .0
.1:
    xor     al,0x20
    cmp     ax,[rdx]
    sbb     rax,rax
    sbb     rax,-1
.2:
    ret

_wcsnicmp endp

    end
