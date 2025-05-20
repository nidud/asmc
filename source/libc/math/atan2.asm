; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

atan2 proc _y:double, _x:double
ifdef _WIN64
   .new x:double = xmm1
   .new y:double = xmm0
else
    define x _x
    define y _y
endif
    fld     y
    fld     x
    fpatan
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

atan2 endp

    end
