; __CVTLD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

__cvtld_q proc x:ptr, ld:ptr

    mov     rax,[rsi]
    movzx   edx,word ptr [rsi+8]
    add     dx,dx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    mov     [rdi],rax
    mov     [rdi+8],rdx
    mov     rax,rdi
    ret

__cvtld_q endp

    end
