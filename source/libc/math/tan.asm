; TAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

tan proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    fld     x
    fptan
    fstp    st(0)
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

tan endp

    end
