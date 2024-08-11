; _LOGB.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_logb proc x:double
ifdef __SSE__
    local   d:double
    movsd   d,xmm0
    fld     d
else
    fld     x
endif
    fxtract
    fstp    st(0)
ifdef __SSE__
    fstp    d
    movsd   xmm0,d
endif
    ret

_logb endp

    end
