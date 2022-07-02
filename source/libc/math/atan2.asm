; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan2 proc y:double, x:double
ifdef __SSE__
  local     a:real8
  local     b:real8
    movsd   a,xmm0
    movsd   b,xmm1
    fld     a
    fld     b
else
    fld     y
    fld     x
endif
    fpatan
ifdef __SSE__
    fstp    b
    movsd   xmm0,b
endif
    ret

atan2 endp

    end
