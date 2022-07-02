; ATANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atanf proc x:float
ifdef __SSE__
  local a:float

    movss   a,xmm0
    fld     a
else
    fld     x
endif
    fld1
    fpatan
ifdef __SSE__
    fstp    a
    movss   xmm0,a
endif
    ret

atanf endp

    end
