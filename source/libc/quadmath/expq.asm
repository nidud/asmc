; EXPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option dotname

expq proc q:real16
ifdef _WIN64
    qtofpu( xmm0 )
    fxam
    fstsw   ax
    fwait
    sahf
    jnp     .0
    jnc     .0
    test    ah,2
    jz      .1
    fstp    st
    fldz
    jmp     .1
.0:
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
.1:
    fputoq()
else
    int 3
endif
    ret
expq endp

    end
