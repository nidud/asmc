; TANHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

ifdef _WIN64

option float: 4

tanhf proc x:float
    .if ( xmm0 > 50.0 )
        movss xmm0,1.0
    .else
        movss xmm2,-50.0
        movss xmm1,xmm0
        movss xmm0,-1.0
        .if ( xmm2 <= xmm1 )
            expf(xmm1)
            movss xmm2,1.0
            movss xmm1,xmm0
            divss xmm2,xmm0
            addss xmm0,xmm2
            subss xmm1,xmm2
            divss xmm1,xmm0
            movss xmm0,xmm1
        .endif
    .endif
    ret
    endp
endif
    end
