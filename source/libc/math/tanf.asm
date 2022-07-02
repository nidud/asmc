; TANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

tanf proc x:float
ifdef __SSE__
  local f:float

    movss f,xmm0
    fld   f
else
    fld   x
endif
    fptan
ifdef __SSE__
    fstp  f
    movss xmm0,f
endif
    ret

tanf endp

    end
