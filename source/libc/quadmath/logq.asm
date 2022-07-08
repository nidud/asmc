; LOGQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

logq proc q:real16
ifdef _WIN64
    qtofpu( xmm0 )
    fldln2
    fxch    st(1)
    fyl2x
    fputoq()
else
    int     3
endif
    ret
logq endp

    end
