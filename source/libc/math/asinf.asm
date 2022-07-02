; ASINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

asinf proc x:float
ifdef _WIN64
    cvtss2sd xmm0,xmm0
    asin(xmm0)
    cvtsd2ss xmm0,xmm0
else
ifdef __SSE__
  local     f:float
    movss   f,xmm0
    fld     f
else
    fld     x
endif
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
ifdef __SSE__
    fstp    f
    movss   xmm0,f
endif
endif
    ret

asinf endp

    end
