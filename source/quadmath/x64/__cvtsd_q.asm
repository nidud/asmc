; _CVTSD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

__cvtsd_q proc x:ptr, d:ptr

    mov     r10,rcx
    mov     rax,[rdx]
    mov     rdx,rax
    shl     rax,11
    sar     rdx,64-12
    and     dx,0x7FF
    jz      L1
    mov     r8,0x8000000000000000
    or      rax,r8
    cmp     dx,0x7FF
    je      L2
    add     dx,0x3FFF-0x03FF
L0:
    add     edx,edx
    rcr     dx,1
    shl     rax,1
    xor     ecx,ecx
    shrd    rcx,rax,16
    shrd    rax,rdx,16
    mov     [r10+8],rax
    mov     [r10],rcx
    mov     rax,r10
    ret
L1:
    test    rax,rax
    jz      L0
    or      edx,0x3FFF-0x03FF+1
    bsr     r8,rax
    mov     ecx,63
    sub     ecx,r8d
    shl     rax,cl
    sub     dx,cx
    jmp     L0
L2:
    or      dh,0x7F
    not     r8
    test    rax,r8
    jz      L0
    not     r8
    shr     r8,1
    or      rax,r8
    jmp     L0

__cvtsd_q endp

    end
