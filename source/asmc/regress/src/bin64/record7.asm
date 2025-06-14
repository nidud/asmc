
; -- additional handling for C-type 64-bit RECORD fields

ifndef __ASMC64__
    .x64
    .model flat
endif

option casemap:none, fieldalign:8

.template T
    x   dd ?
    record
     a  dq :  1 ?
     b  dq :  7 ?
     c  dq :  8 ?
     d  dq : 33 ?
     e  dq : 14 ?
     f  dq :  1 ?
    ends
   .ends

   .code

    assume  rcx:ptr T
    define  mem <[rcx]>

    cmp     mem.a, 0
    cmp     mem.a, 1
    cmp     mem.b, 0
    cmp     mem.b, 127
    cmp     mem.c, 255
    cmp     mem.e, 0x3FFF
    cmp     mem.f, 1

    test    mem.a, 1
    test    mem.b, 127
    test    mem.c, 255
    test    mem.e, 0x3FFF
    test    mem.f, 1

    or      mem.a, 1
    or      mem.b, 127
    or      mem.c, 255
    or      mem.e, 0x3FFF
    or      mem.f, 1

    xor     mem.a, 1
    xor     mem.b, 127
    xor     mem.c, 255
    xor     mem.e, 0x3FFF
    xor     mem.f, 1

    mov     mem.a, 1
    mov     mem.b, 127
    mov     mem.c, 255
    mov     mem.d, 0x1FFFFFFFF
    mov     mem.e, 0x3FFF
    mov     mem.f, 1

    mov     al,mem.a
    mov     al,mem.b
    mov     al,mem.c
    mov     rax,mem.d
    mov     ax,mem.e
    mov     al,mem.f

    mov     mem.a,al
    mov     mem.b,al
    mov     mem.c,al
    mov     mem.d,rax
    mov     mem.e,ax
    mov     mem.f,al

    .if ( mem.a == 0 )      ; TEST/JNZ
    .endif
    .if ( mem.a == 1 )      ; TEST/JZ
    .endif

    end
