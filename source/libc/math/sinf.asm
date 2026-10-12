; SINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

sinf proc x:float
ifdef _WIN64

    option comdat:on

    define C1 -2.3889859E-08
    define C2 +2.7525562E-06
    define C3 -1.9840874E-04
    define C4 +8.3333310E-03
    define C5 -1.6666667E-01

    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm0, _mm_set1_ps(M_R2PI))
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_ps(xmm0, _mm_set1_ps(M_TWOPI))
    _mm_sub_ps(xmm1, xmm0)
    _mm_mov_ps(xmm2, xmm1)
    _mm_and_ps(xmm1, _mm_set1_ps(-0.0))
    _mm_mov_ps(xmm0, xmm1)
    _mm_or_ps(xmm0, _mm_set1_ps(M_PI))
    _mm_mov_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_sub_ps(xmm0, xmm2)
    _mm_cmple_ps(xmm3, _mm_set1_ps(M_PI_2))
    _mm_and_ps(xmm2, xmm3)
    _mm_andnot_ps(xmm3, xmm0)
    _mm_or_ps(xmm2, xmm3)
    _mm_mul_ps(_mm_mov_ps(xmm1, xmm2), xmm2)
    _mm_mul_ps(_mm_mov_ps(xmm0, _mm_set1_ps(C1)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C2)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C3)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C4)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C5)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(1.0)), xmm2)
else
    fld x
    fsin
endif
    ret
    endp

    end
