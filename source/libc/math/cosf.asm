; COSF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; float cosf(float);
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

cosf proc x:float

ifdef _WIN64

    option comdat:on

    define C1 -2.6051615E-07
    define C2 +2.4760495E-05
    define C3 -1.3888378E-03
    define C4 +4.16666436892897E-02

    _mm_store_ps(xmm1, xmm0)
    _mm_round_ps(_mm_mul_ps(xmm0, _mm_set1_ps(M_R2PI)), _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_ps(xmm0, _mm_set1_ps(M_TWOPI))
    _mm_store_ps(xmm2, _mm_sub_ps(xmm1, xmm0))
    _mm_and_ps(xmm1, _mm_set1_ps(-0.0))
    _mm_or_ps(_mm_store_ps(xmm0, xmm1), _mm_set1_ps(M_PI))
    _mm_andnot_ps(_mm_store_ps(xmm3, xmm1), xmm2)
    _mm_sub_ps(xmm0, xmm2)
    _mm_store_ps(xmm4, _mm_cmple_ps(xmm3, _mm_set1_ps(M_PI_2)))
    _mm_and_ps(xmm2, xmm3)
    _mm_or_ps(xmm2, _mm_andnot_ps(xmm3, xmm0))
    _mm_mul_ps(_mm_store_ps(xmm1, xmm2), xmm2)
    _mm_and_ps(_mm_store_ps(xmm2, xmm4), _mm_set1_ps(1.0))
    _mm_or_ps(xmm2, _mm_andnot_ps(xmm4, _mm_set1_ps(-1.0)))
    _mm_mul_ps(_mm_store_ps(xmm0, _mm_set1_ps(C1)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C2)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C3)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(C4)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(-0.5)), xmm1)
    _mm_mul_ps(_mm_add_ps(xmm0, _mm_set1_ps(1.0)), xmm2)
else
    fld x
    fcos
endif
    ret
    endp

    end
