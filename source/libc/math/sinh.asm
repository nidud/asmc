; SINH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
define _USE_MATH_DEFINES
include math.inc

.code

sinh proc x:double
ifdef _WIN64
   .new z:double
    option comdat:on
    mulsd xmm0,M_LOG2E
    movsd xmm1,xmm0
    movsd xmm3,-1.0
    addsd xmm0,xmm3
    subsd xmm3,xmm1
    movsd x,xmm0
    movsd z,exp2(xmm3)
    exp2(x)
    subsd xmm0,z
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
