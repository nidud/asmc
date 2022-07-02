; FMODF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
include intrin.inc

    .code

    option dotname

fmodf proc x:float, y:float
ifdef __SSE__
    movss   xmm2,xmm0
    divss   xmm2,xmm1
    roundss xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulss   xmm2,xmm1
    subss   xmm0,xmm2
else
    fld     x
    fld     y
    fxch    st(1)
.0:
    fprem
    fstsw   ax
    sahf
    jp      .0
    fstp    st(1)
endif
    ret
fmodf endp

    end
