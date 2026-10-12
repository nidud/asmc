; __VDECL_SINHF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef __SSE2__
include intrin.inc
endif

.code

ifdef __SSE2__

__vdecl_sinhf4 proc __vdecl uses xmm6 xmm7 x:XVECTOR
    _mm_mul_ps(xmm0, _mm_set1_ps(M_LOG2E))
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, _mm_set1_ps(-1.0))
    _mm_add_ps(xmm0, xmm3)
    _mm_sub_ps(xmm3, xmm1)
    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, _mm_exp2_ps(xmm3))
    _mm_exp2_ps(xmm6)
    _mm_sub_ps(xmm0, xmm7)
    ret
    endp
endif
    end
