; __CVTI32_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvti32_q proc uses rbx q:ptr, l:long_t

    mov rbx,p
    cvti32_q(l)
    mov rax,rbx
    movups [rax],xmm0
    ret

__cvti32_q endp

    end

