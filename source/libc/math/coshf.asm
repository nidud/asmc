; COSHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; float coshf(float);
;
include math.inc
ifdef _WIN64
include intrin.inc
assume uses xmm6 xmm7
endif

.code

coshf proc x:float
ifdef _WIN64
    mulss xmm0,M_LOG2E
    movss xmm1,xmm0
    movss xmm3,-1.0
    addss xmm0,xmm3
    subss xmm3,xmm1
    movss xmm6,xmm0
    exp2f(xmm3)
    movss xmm7,xmm0
    exp2f(xmm6)
    addss xmm0,xmm7
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
    faddp   st(1),st(0)
    fld1
    fadd    st(0),st(0)
    fdivp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
endif
    ret
    endp

    end
