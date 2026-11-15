; __VDECL_COSF8.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __m256 __vdecl_cosf8(__m256);
;

ifdef __AVX__
include intrin.inc
endif

.code

ifdef __AVX__

    option comdat:on

    define C1 -2.6051615E-07
    define C2 +2.4760495E-05
    define C3 -1.3888378E-03
    define C4 +4.16666436892897E-02

__vdecl_cosf8 proc __vdecl x:yword

    _mm256_mov_ps(ymm1, ymm0)
    _mm256_mul_ps(ymm0, _mm256_set1_ps(M_R2PI))
    _mm256_round_ps(ymm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm256_mul_ps(ymm0, _mm256_set1_ps(M_TWOPI))
    _mm256_mov_ps(ymm2, _mm256_sub_ps(ymm1, ymm0))
    _mm256_and_ps(ymm1, _mm256_set1_ps(-0.0))
    _mm256_or_ps(_mm256_mov_ps(ymm0, ymm1), _mm256_set1_ps(M_PI))
    _mm256_andnot_ps(_mm256_mov_ps(ymm3, ymm1), ymm2)
    _mm256_sub_ps(ymm0, ymm2)
    _mm256_mov_ps(ymm4, _mm256_cmple_ps(ymm3, _mm256_set1_ps(M_PI_2)))
    _mm256_and_ps(ymm2, ymm3)
    _mm256_or_ps(ymm2, _mm256_andnot_ps(ymm3, ymm0))
    _mm256_mul_ps(_mm256_mov_ps(ymm1, ymm2), ymm2)
    _mm256_and_ps(_mm256_mov_ps(ymm2, ymm4), _mm256_set1_ps(1.0))
    _mm256_or_ps(ymm2, _mm256_andnot_ps(ymm4, _mm256_set1_ps(-1.0)))
    _mm256_mul_ps(_mm256_mov_ps(ymm0, _mm256_set1_ps(C1)), ymm1)
    _mm256_mul_ps(_mm256_add_ps(ymm0, _mm256_set1_ps(C2)), ymm1)
    _mm256_mul_ps(_mm256_add_ps(ymm0, _mm256_set1_ps(C3)), ymm1)
    _mm256_mul_ps(_mm256_add_ps(ymm0, _mm256_set1_ps(C4)), ymm1)
    _mm256_mul_ps(_mm256_add_ps(ymm0, _mm256_set1_ps(-0.5)), ymm1)
    _mm256_mul_ps(_mm256_add_ps(ymm0, _mm256_set1_ps(1.0)), ymm2)
    ret
    endp
endif
    end
