; __VDECL_EXPF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __m128 __vdecl_expf4(__m128);
;
include math.inc
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__
__vdecl_expf4 proc __vdecl x:XVECTOR
    exp2f(_mm_mul_ps(xmm0, _mm_set1_ps(M_LOG2E)))
    ret
    endp
endif

    end
