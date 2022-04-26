; __CVTSS_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvtss_q proc uses rbx q:ptr, f:ptr

    mov rbx,q
    movss xmm0,[f]
    cvtss_q(xmm0)
    mov rax,rbx
    movups [rax],xmm0
    ret

__cvtss_q endp

    end
