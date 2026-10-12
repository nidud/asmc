; TANHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

tanhf proc x:float
ifdef _WIN64
    option comdat:on
    mulss xmm0,2.8853900817779268
    exp2f(xmm0)
    mulss xmm0,0.5
    addss xmm0,0.5
    movss xmm1,1.0
    movss xmm2,xmm1
    divss xmm1,xmm0
    subss xmm2,xmm1
    movss xmm0,xmm2
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
