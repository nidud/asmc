; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan2 proc y:double, x:double

  local a:real8
  local b:real8

    movsd   a,xmm0
    movsd   b,xmm1
    fld     a
    fld     b
    fpatan
    fstp    b
    movsd   xmm0,b
    ret

atan2 endp

    end
