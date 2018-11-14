; ATAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
