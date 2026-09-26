; EXPF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; float expf(float);
; __m128 __vdecl_expf4(__m128);
;
include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_expf4
alias <__vdecl_expf4>=<expf>
endif

    .code

expf proc x:float
ifdef _WIN64
   exp2f(_mm_mul_ps(xmm0, g_X4FLOG2E))
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
