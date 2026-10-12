; ACOSF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

acosf proc x:float
ifdef _WIN64

    ; ACOS(-1)= PI, 0 = PI/2, 1 = 0

    option comdat:on

    define C1 -1.262491100E-3
    define C2 +6.670090100E-3
    define C3 -1.708812560E-2
    define C4 +3.089188100E-2
    define C5 -5.017430460E-2
    define C6 +8.897898740E-2
    define C7 -2.145988016E-1

    _mm_cmpge_ps(xmm1, xmm0, _mm_setzero_ps(xmm2))
    _mm_sub_ps(xmm2, xmm0)
    _mm_max_ps(xmm0, xmm2)
    _mm_sub_ps(_mm_store_ps(xmm2, _mm_set1_ps(1.0)), xmm0)
    _mm_setzero_ps(xmm3)
    _mm_sqrt_ps(_mm_max_ps(xmm3, xmm2))
    _mm_mul_ps(_mm_mov_ps(xmm2, _mm_set1_ps(C1)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C2)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C4)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C5)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C6)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C7)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(M_PI_2)), xmm3)
    _mm_store_ps(xmm3, _mm_set1_ps(M_PI))
    _mm_store_ps(xmm0, xmm1)
    _mm_sub_ps(xmm3, xmm2)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(xmm1, xmm3)
    _mm_or_ps(xmm0, xmm1)
else
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
endif
    ret
    endp

    end
