; TANH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

ifdef _WIN64

option float: 8

tanh proc x:double
    .if ( xmm0 > 50.0 )
        movsd xmm0,1.0
    .else
        movsd xmm2,-50.0
        movsd xmm1,xmm0
        movsd xmm0,-1.0
        .if ( xmm2 <= xmm1 )
            exp(xmm1)
            movsd xmm2,1.0
            movsd xmm1,xmm0
            divsd xmm2,xmm0
            addsd xmm0,xmm2
            subsd xmm1,xmm2
            divsd xmm1,xmm0
            movsd xmm0,xmm1
        .endif
    .endif
    ret
    endp
endif
    end
