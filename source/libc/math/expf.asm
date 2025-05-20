; EXPF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option dotname

expf proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
    fld     x
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
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

expf endp

    end
