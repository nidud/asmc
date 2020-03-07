; LOG10QF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

log10qf proc vectorcall Q:real16

    fldq()
    fldlg2
    fxch st(1)
    fyl2x
    fstq()
    ret

log10qf endp

    end
