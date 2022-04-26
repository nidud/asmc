; __CVTQ_SS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_ss() - Quad to float
;

include quadmath.inc

    .code

__cvtq_ss proc uses rbx s:ptr, q:ptr

    mov rbx,s
    movups xmm0,[q]
    cvtq_ss(xmm0)
    mov rax,rbx
    movss [rax],xmm0
    ret

__cvtq_ss endp

    end
