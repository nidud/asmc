; CVTLDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

cvtldq proc ld:real10
ifdef _WIN64
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
else
    int 3
endif
    ret
cvtldq endp

    end
