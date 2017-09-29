; ATAN2.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

atan2 proc __cdecl y:double, x:double

    fld y
    fld x
    fpatan
    ret

atan2 endp

    end
