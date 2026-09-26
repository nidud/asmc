; ATAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan proc x:double

    fld x
    fld1
    fpatan
ifdef _WIN64
    fstp x
    movsd xmm0,x
endif
    ret
    endp

    end
