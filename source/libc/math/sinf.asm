; SINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

sinf proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
    fld     x
    fsin
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

sinf endp

    end
