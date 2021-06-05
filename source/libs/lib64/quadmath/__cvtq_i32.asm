; __CVTQ_I32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i32() - Quadruple float to long
;

include quadmath.inc

    .code

__cvtq_i32 proc q:ptr

    movups xmm0,[rcx]
    cvtq_i32(xmm0)
    ret

__cvtq_i32 endp

    end
