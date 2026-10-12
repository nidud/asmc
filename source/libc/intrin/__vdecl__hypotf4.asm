; __VDECL__HYPOTF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__

__vdecl__hypotf4 proc __vdecl x:XVECTOR, y:XVECTOR
    mulps   xmm0,xmm0
    mulps   xmm1,xmm1
    addps   xmm0,xmm1
    sqrtps  xmm0,xmm0
    ret
    endp
endif
    end
