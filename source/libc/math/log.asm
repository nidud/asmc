; LOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

log proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    fld     x
    fldln2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

log endp

    end
