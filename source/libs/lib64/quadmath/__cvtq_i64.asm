; __CVTQ_I64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i64() - Quadruple float to long long
;

include quadmath.inc

    .code

__cvtq_i64 proc q:ptr

    movups xmm0,[rcx]
    cvtq_i64(xmm0)
    ret

__cvtq_i64 endp

    end
