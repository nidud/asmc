; _CVTSD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvtsd_q proc q:ptr, d:ptr

    movsd xmm0,[rdx]
    cvtsd_q(xmm0)
    mov rax,q
    movups [rax],xmm0
    ret

__cvtsd_q endp

    end
