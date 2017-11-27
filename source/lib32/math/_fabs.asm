; _FABS.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

_fabs proc __cdecl x:double

    fld x
    fabs
    ret

_fabs endp

    end
