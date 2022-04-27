; CVTLD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

cvtld_q proc ld:real10

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movd    edx,xmm0
    and     edx,0xFFFF
    add     dx,dx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1
    ret

cvtld_q endp

    end
