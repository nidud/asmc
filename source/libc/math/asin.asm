; ASIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

asin proc x:double

    fld x
    fld st(0)
    fmul st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
ifdef _WIN64
    fstp x
    movsd xmm0,x
endif
    ret
    endp

    end
