; SQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

sqrt proc x:double

    fld x
    fsqrt
    ret

sqrt endp

    end
