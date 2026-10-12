; FMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

fmod proc x:double, y:double
ifdef _WIN64
    movsd   xmm2,xmm0
    divsd   xmm2,xmm1
    roundsd xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulsd   xmm2,xmm1
    subsd   xmm0,xmm2
else
    fld     x
    fld     y
    fxch    st(1)
L0:
    fprem
    fstsw   ax
    sahf
    jp      L0
    fstp    st(1)
endif
    ret
    endp

    end
