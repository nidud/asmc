; LOGL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

logl proc x:real10
    fld     x
    fldln2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
