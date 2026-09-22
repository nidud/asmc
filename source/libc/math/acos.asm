; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include fltintrn.inc
option float: double
endif

.code

acos proc x:double
ifdef _WIN64
    movsd xmm2,xmm0
    movsd xmm1,1.0
    mulsd xmm0,xmm0
    subsd xmm1,xmm0
    xorpd xmm0,xmm0
    .if ( xmm1 > xmm0 )
        sqrtsd xmm1,xmm1
        divsd xmm2,xmm1
        atan(xmm2)
        movsd xmm1,M_PI_2
        subsd xmm1,xmm0
        movsd xmm0,xmm1
    .elseif ( xmm1 < xmm0 )
        movsd xmm0,NAN
    .elseif ( xmm2 < xmm0 )
        movsd xmm0,M_PI
    .endif
else
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
endif
    ret
    endp

    end
