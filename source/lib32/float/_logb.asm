; _LOGB.ASM--
; Copyright (C) 2017 Asmc Developers
;
include float.inc

.code

_logb proc __cdecl x:REAL8

    fld x
    fxtract
    fstp st(0)
    ret

_logb endp

    end
