; __VDECL__HYPOT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__

__vdecl__hypot2 proc __vdecl x:XVECTOR, y:XVECTOR
    mulpd   xmm0,xmm0
    mulpd   xmm1,xmm1
    addpd   xmm0,xmm1
    sqrtpd  xmm0,xmm0
    ret
    endp
endif
    end
