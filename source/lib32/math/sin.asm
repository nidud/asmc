; SIN.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

sin proc x:double

    fld x
    fsin
    ret

sin endp

    end
