; __VDECL_FMOD2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__

__vdecl_fmod2 proc __vdecl x:XVECTOR, y:XVECTOR
    movapd  xmm2,xmm0
    divpd   xmm2,xmm1
    roundpd xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulpd   xmm2,xmm1
    subpd   xmm0,xmm2
    ret
    endp
endif
    end
