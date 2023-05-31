; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

_memicmp proc uses rbx a:ptr, b:ptr, size:size_t

    ldr     rbx,size
    ldr     rcx,a
    ldr     rdx,b
    dec     rcx
    dec     rdx
.0:
    test    rbx,rbx
    jz      .3
    dec     rbx
    inc     rdx
    inc     rcx
    mov     al,[rcx]
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
    sbb     rbx,rbx
    sbb     rbx,-1
.3:
    mov     rax,rbx
    ret

_memicmp endp

    end
