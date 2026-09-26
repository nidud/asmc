; TANH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

tanh proc x:double
ifdef _WIN64
    option float: 8
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
else
    fld     x
    fldl2e
    fadd    st(0),st(0)
    fmulp   st(1),st(0)
    fld     st(0)
    frndint
    fsub    st(1),st(0)
    fxch    st(1)
    f2xm1
    fld1
    faddp   st(1),st(0)
    fscale
    fld1
    fsubp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
    fld     st(0)
    fld1
    fadd    st(0),st(0)
    faddp   st(1),st(0)
    fdivp   st(1),st(0)
    ret
endif
    ret
    endp

    end
