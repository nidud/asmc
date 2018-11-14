; COS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

cos proc x:REAL8

    fld x
    fcos
    ret

cos endp

    end
