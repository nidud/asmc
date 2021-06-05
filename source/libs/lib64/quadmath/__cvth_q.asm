; __CVTH_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvth_q proc q:ptr, h:ptr

    movd xmm0,[rdx]
    cvth_q(xmm0)
    mov rax,q
    movups [rax],xmm0
    ret

__cvth_q endp

    end
