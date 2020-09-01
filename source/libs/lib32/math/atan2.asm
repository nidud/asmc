; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
