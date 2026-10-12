; EXPF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; float expf(float);
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

    .code

expf proc x:float
ifdef _WIN64
    mulss xmm0,M_LOG2E
    exp2f(xmm0)
else
    fld     x
    fxam
    fstsw   ax
    fwait
    sahf
    jnp     L0
    jnc     L0
    test    ah,2
    jz      L1
    fstp    st
    fldz
    jmp     L1
L0:
    fldl2e
    fmul    st,st(1)
    fst     st(1)
    frndint
    fxch    st(1)
    fsub    st,st(1)
    f2xm1
    fld1
    faddp   st(1),st
    fscale
    fstp    st(1)
L1:
endif
    ret
    endp

    end
