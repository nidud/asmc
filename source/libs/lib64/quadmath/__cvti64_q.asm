; __CVTI64_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvti64_q() - long long to Quadruple float
;

include quadmath.inc

    .code

__cvti64_q proc q:ptr, ll:int64_t

    cvti64_q(rdx)
    mov rax,q
    movups [rax],xmm0
    ret

__cvti64_q endp

    end

