; TANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
assume uses xmm6 xmm7
endif

.code

tanf proc x:float

ifdef _WIN64

    option comdat:on

    define C1 +6.077100628E-11
    define C2 -1.786170734E-05
    define C3 +3.424887824E-03
    define C4 +4.981943399E-07
    define C5 -3.118153191E-04
    define C6 -1.333835001E-01
    define C7 +2.566383229E-02
    define C8 -4.667168334E-01
    define C9 +2.441406250E-04

    _mm_mov_ps(xmm3, xmm0)
    _mm_mov_ps(xmm7, xmm0)
    _mm_mul_ps(xmm0, _mm_set1_ps(M_2_PI))
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_ps(_mm_mov_ps(xmm1, _mm_set1_ps(M_PI_2)), xmm0)
    _mm_sub_ps(xmm3, xmm1)
    _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(xmm6), xmm0), xmm0)
    _mm_mul_ps(xmm0, _mm_set1_ps(C1))
    _mm_sub_ps(xmm3, xmm0)
    _mm_mov_ps(xmm1, _mm_mul_ps(_mm_mov_ps(xmm0, xmm3), xmm0))
    _mm_add_ps(_mm_mul_ps(xmm0, _mm_set1_ps(C2)), _mm_set1_ps(C3))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C6))
    _mm_add_ps(_mm_mul_ps(_mm_mul_ps(xmm0, xmm1), xmm3), xmm3)
    _mm_mul_ps(_mm_mov_ps(xmm5, _mm_set1_ps(C4)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm5, _mm_set1_ps(C5)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm5, _mm_set1_ps(C7)), xmm1)
    _mm_add_ps(xmm5, _mm_set1_ps(C8))
    _mm_mov_ps(xmm2, _mm_set1_ps(C9))
    _mm_cmple_ps(_mm_mov_ps(xmm4, xmm3), xmm2)
    _mm_mul_ps(xmm2, _mm_set1_ps(-1.0))
    _mm_cmple_ps(xmm2, xmm3)
    _mm_and_ps(xmm4, xmm2)
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), _mm_set1_ps(1.0))
    _mm_mov_ps(xmm2, xmm4)
    _mm_and_ps(xmm3, xmm2)
    _mm_andnot_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, xmm3)
    _mm_mov_ps(xmm3, _mm_set1_ps(1.0))
    _mm_and_ps(xmm3, xmm4)
    _mm_andnot_ps(xmm4, xmm5)
    _mm_or_ps(xmm4, xmm3)
    _mm_sub_ps(_mm_setzero_ps(), xmm2)
    _mm_div_ps(xmm2, xmm4)
    _mm_div_ps(xmm4, xmm0)
    _mm_and_ps(_mm_cvttps_epi32(xmm6), { 1, 1, 1, 1 })
    _mm_cmpeq_epi32(xmm6, _mm_setzero_ps())
    _mm_cmpeq_ps(xmm0, xmm7)
    _mm_and_ps(xmm2, xmm6)
    _mm_andnot_ps(xmm6, xmm4)
    _mm_or_ps(xmm6, xmm2)
    _mm_andnot_ps(xmm0, xmm6)
else
    fld x
    fptan
    fstp st(0)
endif
    ret
    endp

    end
