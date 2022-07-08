; FMODQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option dotname

fmodq proc X:real16, Y:real16
ifdef _WIN64
    qtofpu( xmm0 )
    qtofpu( xmm1 )
    fxch    st(1)
.0:
    fprem
    fstsw   ax
    sahf
    jp      .0
    fstp    st(1)
    fputoq()
else
    int     3
endif
    ret
fmodq endp

    end
