; _FABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

_fabs proc __cdecl x:double

    fld x
    fabs
    ret

_fabs endp

    end
