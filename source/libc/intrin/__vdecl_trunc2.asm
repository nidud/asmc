; __VDECL_TRUNC2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__ ; SSE4.1

__vdecl_trunc2 proc __vdecl x:XVECTOR
    _mm_round_pd(xmm0, _MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC)
    ret
    endp
endif
    end
