; LOG10F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

log10f proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
    fld     x
    fldlg2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

log10f endp

    end
