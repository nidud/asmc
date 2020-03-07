; LOGQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

logqf proc vectorcall Q:real16

    fldq()
    fldln2
    fxch st(1)
    fyl2x
    fstq()
    ret

logqf endp

    end
