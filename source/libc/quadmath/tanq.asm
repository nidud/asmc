; TANQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

tanq proc q:real16
ifdef _WIN64
    qtofpu( xmm0 )
    fptan
    fstp    st(0)
    fputoq()
else
    int     3
endif
    ret
tanq endp

    end
