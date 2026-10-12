; ATANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

atanf proc x:float
ifdef _WIN64

    option comdat:on

    define C1 +2.866225700E-3
    define C2 -1.616573670E-2
    define C3 +4.290961380E-2
    define C4 -7.528964000E-2
    define C5 +1.065626393E-1
    define C6 -1.420889944E-1
    define C7 +1.999355085E-1
    define C8 -3.333314228E-1

    _mm_store_ps(xmm3, _mm_set1_ps(1.0))
    _mm_cmpgt_ps(xmm2, xmm0, xmm3)
    _mm_store_ps(xmm1, xmm2)
    _mm_and_ps(xmm1, xmm3)
    _mm_andnot_ps(xmm2, _mm_set1_ps(-1.0))
    _mm_or_ps(xmm2, xmm1)
    _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(xmm5), xmm0), xmm0)
    _mm_cmple_ps(xmm5, xmm3)
    _mm_store_ps(xmm1, xmm5)
    _mm_store_ps(xmm4, xmm5)
    _mm_andnot_ps(xmm5, xmm2)
    _mm_and_ps(xmm1, xmm0)
    _mm_andnot_ps(xmm4, _mm_div_ps(xmm3, xmm0))
    _mm_or_ps(xmm1, xmm4)
    _mm_mul_ps(_mm_store_ps(xmm0, xmm1), xmm0)
    _mm_mul_ps(_mm_mov_ps(xmm2, _mm_set1_ps(C1)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C2)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C4)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C5)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C6)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C7)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(C8)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_set1_ps(1.0)), xmm1)
    _mm_store_ps(xmm0, xmm5)
    _mm_sub_ps(_mm_mul_ps(xmm5, _mm_set1_ps(M_PI_2)), xmm2)
    _mm_cmpeq_ps(xmm0, _mm_setzero_ps(xmm3))
    _mm_store_ps(xmm3, xmm0)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(xmm3, xmm5)
    _mm_or_ps(xmm0, xmm3)
else
    fld x
    fld1
    fpatan
endif
    ret
    endp

    end
