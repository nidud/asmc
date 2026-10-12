; FMODL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

fmodl proc x:real10, y:real10
    fld     x
    fld     y
    fxch    st(1)
L0:
    fprem
    fstsw   ax
    sahf
    jp      L0
    fstp    st(1)
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
