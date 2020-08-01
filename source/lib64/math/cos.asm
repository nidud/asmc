; COS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

cos proc x:double

  local d:double

    movsd   d,xmm0
    fld     d
    fcos
    fstp    d
    movsd   xmm0,d
    ret

cos endp

    end
