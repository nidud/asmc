; ATAN2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan2f proc _y:float, _x:float
ifdef _WIN64
   .new x:float = xmm1
   .new y:float = xmm0
else
    define x _x
    define y _y
endif
    fld     y
    fld     x
    fpatan
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

atan2f endp

    end
