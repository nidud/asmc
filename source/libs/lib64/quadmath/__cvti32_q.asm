; __CVTI32_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvti32_q proc q:ptr, l:long_t

    cvti32_q(edx)
    mov rax,q
    movups [rax],xmm0
    ret

__cvti32_q endp

    end

