; LOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

log proc x:double
ifdef __SSE__
  local     d:double
    movsd   d,xmm0
    fld     d
else
    fld     x
endif
    fldln2
    fxch    st(1)
    fyl2x
ifdef __SSE__
    fstp    d
    movsd   xmm0,d
endif
    ret

log endp

    end
