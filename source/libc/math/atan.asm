; ATAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan proc x:double
ifdef __SSE__
  local a:real8

    movsd   a,xmm0
    fld     a
else
    fld     x
endif
    fld1
    fpatan
ifdef __SSE__
    fstp    a
    movsd   xmm0,a
endif
    ret

atan endp

    end
