; __VDECL_COS2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include intrin.inc

.code

ifdef __SSE2__

    option comdat:on

    define C1 -2.6051615E-07
    define C2 +2.4760495E-05
    define C3 -1.3888378E-03
    define C4 +4.16666436892897E-02

__vdecl_cos2 proc __vdecl x:XVECTOR
    _mm_move_pd(xmm1, xmm0)
    _mm_mul_pd(xmm0, _mm_set1_pd(M_R2PI))
    _mm_round_pd(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_pd(xmm0, _mm_set1_pd(M_TWOPI))
    _mm_sub_pd(xmm1, xmm0)
    _mm_move_pd(xmm2, xmm1)
    _mm_and_pd(xmm1, _mm_set1_pd(-0.0))
    _mm_move_pd(xmm0, xmm1)
    _mm_or_pd(xmm0, _mm_set1_pd(M_PI))
    _mm_move_pd(xmm3, xmm1)
    _mm_andnot_pd(xmm3, xmm2)
    _mm_sub_pd(xmm0, xmm2)
    _mm_cmple_pd(xmm3, _mm_set1_pd(M_PI_2))
    _mm_move_pd(xmm4, xmm3)
    _mm_and_pd(xmm2, xmm3)
    _mm_andnot_pd(xmm3, xmm0)
    _mm_or_pd(xmm2, xmm3)
    _mm_move_pd(xmm1, xmm2)
    _mm_mul_pd(xmm1, xmm2)
    _mm_move_pd(xmm2, xmm4)
    _mm_and_pd(xmm2, _mm_set1_pd(1.0))
    _mm_andnot_pd(xmm4, _mm_set1_pd(-1.0))
    _mm_or_pd(xmm2, xmm4)
    _mm_mul_pd(_mm_move_pd(xmm0, _mm_set1_pd(C1)), xmm1)
    _mm_mul_pd(_mm_add_pd( xmm0, _mm_set1_pd(C2)), xmm1)
    _mm_mul_pd(_mm_add_pd( xmm0, _mm_set1_pd(C3)), xmm1)
    _mm_mul_pd(_mm_add_pd( xmm0, _mm_set1_pd(C4)), xmm1)
    _mm_mul_pd(_mm_add_pd( xmm0, _mm_set1_pd(-0.5)), xmm1)
    _mm_mul_pd(_mm_add_pd( xmm0, _mm_set1_pd(1.0)), xmm2)
    ret
    endp
endif
    end
