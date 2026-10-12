; ATAN2L.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

atan2l proc y:real10, x:real10
    fld     y
    fld     x
    fpatan
ifdef _WIN64
    fstp    y
    movaps  xmm0,xmmword ptr y
endif
    ret
    endp

    end
