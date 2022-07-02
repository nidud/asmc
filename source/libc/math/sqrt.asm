; SQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;


include math.inc

    .code

sqrt proc x:double
ifdef __SSE__
    sqrtsd  xmm0,xmm0
else
    fld     x
    fsqrt
endif
    ret

sqrt endp

    end
