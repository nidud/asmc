; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname
ifndef _WIN64
    assume uses esi
    define r8 <esi>
endif

_memicmp proc a:ptr, b:ptr, size:size_t
    ldr     r8,size
    ldr     rcx,a
    ldr     rdx,b
    sub     rdx,rcx
.0:
    test    r8,r8
    jz      .3
    dec     r8
    mov     al,[rcx]
    mov     ah,[rcx+rdx]
    inc     rcx
    cmp     al,ah
    je      .0
    cmp     al,'A'
    jb      .1
    cmp     al,'Z'
    ja      .1
    add     al,'a'-'A'
.1:
    cmp     ah,'A'
    jb      .2
    cmp     ah,'Z'
    ja      .2
    add     ah,'a'-'A'
.2:
    cmp     al,ah
    je      .0
    sbb     r8,r8
    sbb     r8,-1
.3:
    mov     rax,r8
    ret
    endp

    end
