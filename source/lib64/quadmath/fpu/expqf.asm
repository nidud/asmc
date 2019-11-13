; EXPQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

expqf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld x
    fxam
    fstsw ax
    fwait
    sahf
    .if PARITY? && CARRY?

        .if ah & 2

            fstp st
            fldz
        .endif
    .else
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
    .endif
    fstp x
    _mm_cvtld_q(x)
    ret

expqf endp

    end
