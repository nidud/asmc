; FMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_fmod2
alias <__vdecl_fmod2>=<fmod>
endif

    .code

    option dotname

fmod proc x:double, y:double
ifdef _WIN64
    movapd  xmm2,xmm0
    divpd   xmm2,xmm1
    roundpd xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulpd   xmm2,xmm1
    subpd   xmm0,xmm2
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
    endp

    end
