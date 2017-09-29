; ATAN.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

atan proc __cdecl x:double

    fld x
    fld1
    fpatan
    ret

atan endp

    end
