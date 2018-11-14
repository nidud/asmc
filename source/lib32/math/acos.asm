; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

acos proc __cdecl x:double

    fld	   x
    fmul   st(0),st(0)
    fld1
    fsubrp st(1),st(0)
    fsqrt
    fld	   x
    fpatan
    ret

acos endp

    end
