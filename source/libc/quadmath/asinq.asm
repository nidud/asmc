; ASINQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

asinq proc x:real16
ifdef _WIN64
    qtofpu( xmm0 )
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
    fputoq()
else
    int 3
endif
    ret
asinq endp

    end
