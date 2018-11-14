; SIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

sin proc x:double

    fld x
    fsin
    ret

sin endp

    end
