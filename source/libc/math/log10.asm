; LOG10.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

log10 proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    fld     x
    fldlg2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

log10 endp

    end
