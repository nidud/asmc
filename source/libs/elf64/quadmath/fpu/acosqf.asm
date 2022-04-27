; ACOSQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

acosqf proc q:real16

    fldq()
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     d
    fpatan
    fstq()
    ret

acosqf endp

    end
