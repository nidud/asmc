; SQRTL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

sqrtl proc x:real10
    fld     x
    fsqrt
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
