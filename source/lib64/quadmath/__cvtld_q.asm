; __CVTLD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

__cvtld_q proc x:ptr, ld:ptr

    mov     rax,[rdx]
    movzx   edx,word ptr [rdx+8]
    add     dx,dx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    mov     [rcx],rax
    mov     [rcx+8],rdx
    mov     rax,rcx
    ret

__cvtld_q endp

    end
