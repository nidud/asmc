; ACOSF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

acosf proc x:float
ifdef __SSE__
    cvtss2sd xmm0,xmm0
    acos( xmm0 )
    cvtsd2ss xmm0,xmm0
else
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
endif
    ret

acosf endp

    end
