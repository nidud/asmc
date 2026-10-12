; __VDECL_FMODF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__

__vdecl_fmodf4 proc __vdecl x:XVECTOR, y:XVECTOR
    movaps  xmm2,xmm0
    divps   xmm2,xmm1
    roundps xmm2,xmm2,_MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC
    mulps   xmm2,xmm1
    subps   xmm0,xmm2
    ret
    endp
endif
    end
