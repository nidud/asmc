; _LOGB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_logb proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    fld     x
    fxtract
    fstp    st(0)
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

_logb endp

    end
