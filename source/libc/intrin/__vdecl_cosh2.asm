; __VDECL_COSH2.ASM--
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

    option comdat:on

__vdecl_cosh2 proc __vdecl x:XVECTOR
    _mm_exp_pd(_mm_and_pd(xmm0, _mm_set1_pd(0x7FFFFFFFFFFFFFFF)))
    _mm_move_pd(xmm1, _mm_set1_pd(1.0))
    _mm_div_pd(xmm1, xmm0)
    _mm_add_pd(xmm0, xmm1)
    _mm_mul_pd(xmm0, _mm_set1_pd(0.5))
    ret
    endp
endif
    end
