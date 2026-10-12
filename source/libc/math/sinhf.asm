; SINHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
define _USE_MATH_DEFINES
include math.inc

.code

sinhf proc x:float
ifdef _WIN64
   .new z:float
    option comdat:on
    mulss xmm0,M_LOG2E
    movss xmm1,xmm0
    movss xmm3,-1.0
    addss xmm0,xmm3
    subss xmm3,xmm1
    movss x,xmm0
    movss z,exp2f(xmm3)
    exp2f(x)
    subss xmm0,z
else
    fld     x
    fldl2e
    fmul    st(0),st(1)
    fld     st(0)
    frndint
    fsub    st(1),st(0)
    fxch    st(1)
    f2xm1
    fld1
    faddp   st(1),st(0)
    fscale
    fst     st(1)
    fld1
    fdivrp  st(1),st(0)
    fsubp   st(1),st(0)
    fld1
    fadd    st(0),st(0)
    fdivp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
endif
    ret
    endp

    end
