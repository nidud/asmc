; EXPL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

expl proc x:real10
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
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
