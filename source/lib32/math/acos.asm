; ACOS.ASM--
; Copyright (C) 2017 Asmc Developers
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
