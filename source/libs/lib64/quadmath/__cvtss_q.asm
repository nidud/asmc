; __CVTSS_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvtss_q proc q:ptr, f:ptr

    movss xmm0,[rdx]
    cvtss_q(xmm0)
    mov rax,q
    movups [rax],xmm0
    ret

__cvtss_q endp

    end
