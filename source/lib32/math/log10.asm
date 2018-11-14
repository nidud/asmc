; LOG10.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
