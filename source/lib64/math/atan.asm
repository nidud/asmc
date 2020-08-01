; ATAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan proc x:double

  local a:real8

    movsd   a,xmm0
    fld     a
    fld1
    fpatan
    fstp    a
    movsd   xmm0,a
    ret

atan endp

    end
