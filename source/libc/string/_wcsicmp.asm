; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_wcsicmp proc a:wstring_t, b:wstring_t

    ldr     rcx,a
    ldr     rdx,b

    sub     rcx,2
    sub     rdx,2
    mov     eax,1
.0:
    test    eax,eax
    jz      .2
    add     rcx,2
    add     rdx,2
    mov     ax,[rcx]
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

_wcsicmp endp

    end
