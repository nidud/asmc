; _LOGB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
