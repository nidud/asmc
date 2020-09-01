; TANQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

tanqf proc __vectorcall Q:real16

    fldq()
    fptan
    fstp st(0)
    fstq()
    ret

tanqf endp

    end
