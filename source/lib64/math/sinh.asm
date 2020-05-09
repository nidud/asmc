; SINH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:nosave

sinh proc x:double

    comisd xmm0,0.0
    .ifnb
        exp(xmm0)
        movsd xmm1,1.0
        divsd xmm1,xmm0
        subsd xmm0,xmm1
        mulsd xmm0,0.5
    .else
        movsd xmm1,-0.0
        xorpd xmm0,xmm1
        exp(xmm0)
        movsd xmm1,1.0
        divsd xmm1,xmm0
        subsd xmm1,xmm0
        movsd xmm0,0.5
        mulsd xmm0,xmm1
    .endif
    ret

sinh endp

    end
