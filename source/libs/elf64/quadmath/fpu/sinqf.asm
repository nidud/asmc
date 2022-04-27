; SINQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

sinqf proc Q:real16

    fldq()
    fsin
    fstq()
    ret

sinqf endp

    end
