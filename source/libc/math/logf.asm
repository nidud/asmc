; LOGF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

logf proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
    fld     x
    fldln2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

logf endp

    end
