; COS.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

cos proc x:REAL8

    fld x
    fcos
    ret

cos endp

    end
