; _CVTSD_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvtsd_q proc uses rbx q:ptr, d:ptr

    mov rbx,q
    movsd xmm0,[d]
    cvtsd_q(xmm0)
    mov rax,rbx
    movups [rax],xmm0
    ret

__cvtsd_q endp

    end
