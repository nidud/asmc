; COSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:nosave

cosh proc x:REAL8

    exp(_fabs(xmm0))
    movsd xmm1,1.0
    divsd xmm1,xmm0
    addsd xmm0,xmm1
    divsd xmm0,2.0
    ret

cosh endp

    end
