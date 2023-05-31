; _STRNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_strnicmp proc uses rbx a:string_t, b:string_t, size:size_t

    ldr     rbx,a
    ldr     rcx,size
    ldr     rdx,b

    dec     rbx
    dec     rdx
    mov     eax,1
.0:
    test    eax,eax
    jz      .3
    inc     rbx
    inc     rdx
    xor     eax,eax
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     al,[rbx]
    cmp     al,[rdx]
    je      .0

    cmp     al,'A'
    jb      .1
    cmp     al,'Z'
    ja      .1
    or      al,0x20
.1:
    mov     ah,[rdx]
    cmp     ah,'A'
    jb      .2
    cmp     ah,'Z'
    ja      .2
    or      ah,0x20
.2:
    cmp     al,ah
    mov     ah,0
    je      .0
    sbb     rax,rax
    sbb     rax,-1
.3:
    ret

_strnicmp endp

    end
