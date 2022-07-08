; TAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

tan proc x:double
ifdef __SSE__
  local d:double
    movsd d,xmm0
    fld   d
else
    fld   x
endif
    fptan
    fstp    st(0)
ifdef __SSE__
    fstp  d
    movsd xmm0,d
endif
    ret
tan endp

    end
