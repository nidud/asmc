; ATAN2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan2f proc x:float, y:float
ifdef __SSE__
  local a:float
  local b:float

    movss   a,xmm0
    movss   b,xmm1
    fld     a
    fld     b
else
    fld     x
    fld     y
endif
    fpatan
ifdef __SSE__
    fstp    a
    movss   xmm0,a
endif
    ret

atan2f endp

    end
