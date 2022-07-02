; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

acos proc x:double
ifdef __SSE__
    movsd  xmm1,xmm0
    movsd  xmm2,xmm0
    movsd  xmm0,1.0
    mulsd  xmm2,xmm2
    subsd  xmm0,xmm2
    sqrtpd xmm0,xmm0
    atan2( xmm0, xmm1 )
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

acos endp

    end
