; __VDECL_ASIN2.ASM--
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

    define C1 -1.262491100E-3
    define C2 +6.670090100E-3
    define C3 -1.708812560E-2
    define C4 +3.089188100E-2
    define C5 -5.017430460E-2
    define C6 +8.897898740E-2
    define C7 -2.145988016E-1

__vdecl_asin2 proc __vdecl x:XVECTOR

    _mm_cmpge_pd(xmm1, xmm0, _mm_setzero_pd(xmm2))
    _mm_sub_pd(xmm2, xmm0)
    _mm_max_pd(xmm0, xmm2)
    _mm_sub_pd(_mm_store_pd(xmm2, _mm_set1_pd(1.0)), xmm0)
    _mm_setzero_pd(xmm3)
    _mm_sqrt_pd(_mm_max_pd(xmm3, xmm2))
    _mm_mul_pd(_mm_mov_pd(xmm2, _mm_set1_pd(C1)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C2)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C3)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C4)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C5)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C6)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C7)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(M_PI_2)), xmm3)
    _mm_store_pd(xmm0, _mm_set1_pd(M_PI))
    _mm_store_pd(xmm3, xmm1)
    _mm_sub_pd(xmm0, xmm2)
    _mm_and_pd(xmm3, xmm2)
    _mm_andnot_pd(xmm1, xmm0)
    _mm_or_pd(xmm3, xmm1)
    _mm_store_pd(xmm0, _mm_set1_pd(M_PI_2))
    _mm_sub_pd(xmm0, xmm3)
    ret
    endp
endif
    end
