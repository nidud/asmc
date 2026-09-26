; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

atan2 proc y:double, x:double
    fld y
    fld x
    fpatan
ifdef _WIN64
    fstp x
    movsd xmm0,x
endif
    ret
    endp

    end
