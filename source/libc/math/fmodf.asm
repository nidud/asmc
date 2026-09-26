; FMODF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_fmodf4
alias <__vdecl_fmodf4>=<fmodf>
endif

.code

fmodf proc x:float, y:float
ifdef _WIN64
    _mm_fmod_ss(xmm0, xmm1)
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
