; FPUTOQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

fputoq proc
ifdef _WIN64
   .new     ld:real10
    fstp    ld
    mov     rax,qword ptr ld
    mov     dx,word ptr ld[8]
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
    int     3
endif
    ret
fputoq endp

    end
