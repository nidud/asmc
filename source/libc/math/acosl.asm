; ACOSL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

acosl proc x:real10
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
