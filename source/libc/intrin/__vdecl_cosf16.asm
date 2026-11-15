; __VDECL_COSF16.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __m512 __vdecl_cosf16(__m512);
;

ifdef __AVX512F__
include intrin.inc
endif

.code

ifdef __AVX512F__

    option comdat:on

    define C1 -2.6051615E-07
    define C2 +2.4760495E-05
    define C3 -1.3888378E-03
    define C4 +4.16666436892897E-02

__vdecl_cosf16 proc __vdecl x:zword

    _mm512_mov_ps(zmm1, zmm0)
    _mm512_mul_ps(zmm0, _mm512_set1_ps(M_R2PI, zmm2))
    _mm512_roundscale_ps(zmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm512_mul_ps(zmm0, _mm512_set1_ps(M_TWOPI, zmm2))
    _mm512_mov_ps(zmm2, _mm512_sub_ps(zmm1, zmm0))

    _mm512_set1_ps(-0.0, zmm3)
    _mm512_and_ps(zmm1, zmm3)
    _mm512_or_ps(_mm512_mov_ps(zmm0, zmm1), _mm512_set1_ps(M_PI, zmm3))
    _mm512_andnot_ps(_mm512_mov_ps(zmm3, zmm1), zmm2)
    _mm512_sub_ps(zmm0, zmm2)
    _mm512_mov_ps(zmm4, _mm512_cmple_ps(zmm3, _mm512_set1_ps(M_PI_2, zmm4)))
    _mm512_and_ps(zmm2, zmm3)
    _mm512_or_ps(zmm2, _mm512_andnot_ps(zmm3, zmm0))
    _mm512_mul_ps(_mm512_mov_ps(zmm1, zmm2), zmm2)
    _mm512_and_ps(_mm512_mov_ps(zmm2, zmm4), _mm512_set1_ps(1.0, zmm3))
    _mm512_or_ps(zmm2, _mm512_andnot_ps(zmm4, _mm512_set1_ps(-1.0, zmm3)))
    _mm512_mul_ps(_mm512_mov_ps(zmm0, _mm512_set1_ps(C1, zmm3)), zmm1)
    _mm512_mul_ps(_mm512_add_ps(zmm0, _mm512_set1_ps(C2, zmm3)), zmm1)
    _mm512_mul_ps(_mm512_add_ps(zmm0, _mm512_set1_ps(C3, zmm3)), zmm1)
    _mm512_mul_ps(_mm512_add_ps(zmm0, _mm512_set1_ps(C4, zmm3)), zmm1)
    _mm512_mul_ps(_mm512_add_ps(zmm0, _mm512_set1_ps(-0.5, zmm3)), zmm1)
    _mm512_mul_ps(_mm512_add_ps(zmm0, _mm512_set1_ps(1.0, zmm3)), zmm2)
    ret
    endp
endif
    end
