; __VDECL_TANHF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef __SSE2__
include intrin.inc
option comdat:on
endif

.code

ifdef __SSE2__

__vdecl_tanhf proc __vdecl x:XVECTOR
    _mm_exp2_ps(_mm_mul_ps(xmm0, _mm_set1_ps(2.8853900817779268)))
    _mm_mul_ps(xmm0, _mm_set1_ps(0.5))
    _mm_add_ps(xmm0, _mm_set1_ps(0.5))
    _mm_store_ps(xmm1, _mm_set1_ps(1.0))
    _mm_store_ps(xmm2, xmm1)
    _mm_div_ps(xmm1, xmm0)
    _mm_sub_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm2)
    ret
    endp
endif

    end
