; SQRTQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

sqrtqf proc vectorcall Q:real16

    fldq()
    fsqrt
    fstq()
    ret

sqrtqf endp

    end
