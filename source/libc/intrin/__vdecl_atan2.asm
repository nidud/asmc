; __VDECL_ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

ifdef __SSE2__

    option comdat:on

    define C1 +2.866225700E-3
    define C2 -1.616573670E-2
    define C3 +4.290961380E-2
    define C4 -7.528964000E-2
    define C5 +1.065626393E-1
    define C6 -1.420889944E-1
    define C7 +1.999355085E-1
    define C8 -3.333314228E-1

__vdecl_atan2 proc __vdecl x:XVECTOR

    _mm_store_pd(xmm3, _mm_set1_pd(1.0))
    _mm_cmpgt_pd(xmm2, xmm0, xmm3)
    _mm_store_pd(xmm1, xmm2)
    _mm_and_pd(xmm1, xmm3)
    _mm_andnot_pd(xmm2, _mm_set1_pd(-1.0))
    _mm_or_pd(xmm2, xmm1)
    _mm_max_pd(_mm_sub_pd(_mm_setzero_pd(xmm5), xmm0), xmm0)
    _mm_cmple_pd(xmm5, xmm3)
    _mm_store_pd(xmm1, xmm5)
    _mm_store_pd(xmm4, xmm5)
    _mm_andnot_pd(xmm5, xmm2)
    _mm_and_pd(xmm1, xmm0)
    _mm_andnot_pd(xmm4, _mm_div_pd(xmm3, xmm0))
    _mm_or_pd(xmm1, xmm4)
    _mm_mul_pd(_mm_mov_pd(xmm0, xmm1), xmm0)
    _mm_mul_pd(_mm_mov_pd(xmm2, _mm_set1_pd(C1)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C2)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C3)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C4)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C5)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C6)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C7)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(C8)), xmm0)
    _mm_mul_pd(_mm_add_pd(xmm2, _mm_set1_pd(1.0)), xmm1)
    _mm_store_pd(xmm0, xmm5)
    _mm_sub_pd(_mm_mul_pd(xmm5, _mm_set1_pd(M_PI_2)), xmm2)
    _mm_cmpeq_pd(xmm0, _mm_setzero_pd(xmm3))
    _mm_store_pd(xmm3, xmm0)
    _mm_and_pd(xmm0, xmm2)
    _mm_andnot_pd(xmm3, xmm5)
    _mm_or_pd(xmm0, xmm3)
    ret
    endp
endif

    end
