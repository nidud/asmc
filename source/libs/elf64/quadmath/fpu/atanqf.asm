; ATANQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

atanqf proc Q:real16

    fldq()
    fld1
    fpatan
    fstq()
    ret

atanqf endp

    end
