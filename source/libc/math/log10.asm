; LOG10.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

log10 proc x:double

    fld x
    fldlg2
    fxch st(1)
    fyl2x
    ret

log10 endp

    end
