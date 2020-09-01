; TAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

tan proc x:double

  local d:double

    movsd d,xmm0
    fld   d
    fptan
    fstp  d
    movsd xmm0,d
    ret

tan endp

    end
