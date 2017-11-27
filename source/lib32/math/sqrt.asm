; SQRT.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

sqrt proc x:double

    fld x
    fsqrt
    ret

sqrt endp

    end
