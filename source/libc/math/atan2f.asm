; ATAN2F.ASM--
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

atan2f proc y:float, x:float
ifdef _WIN64

  local Pi:     XVECTOR,
        Pi_2:   XVECTOR,
        Pi_4:   XVECTOR,
        Pi3_4:  XVECTOR

    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm1)
    _mm_store_ps(xmm5, _mm_atan_ps(_mm_div_ps(xmm0, xmm1)))
    _mm_store_ps(xmm1, _mm_set1_ps(-0.0))
    _mm_and_ps(_mm_store_ps(xmm4, xmm7), xmm1)
    _mm_cmpeq_epi32(xmm4, _mm_set1_ps(0.0))
    _mm_store_ps(xmm2, xmm6)
    _mm_and_ps(xmm2, _mm_set1_ps(-0.0))
    _mm_store_ps(xmm0, xmm2)
    _mm_or_si128(xmm0, _mm_set1_ps(M_PI))
    _mm_store_ps(Pi, xmm0)
    _mm_store_ps(xmm0, _mm_set1_ps(M_PI_2))
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi_2, xmm0)
    _mm_store_ps(xmm0, _mm_set1_ps(M_PI_4))
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi_4, xmm0)
    _mm_store_ps(xmm0, _mm_set1_ps(M_3PI_4))
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi3_4, xmm0)
    _mm_store_ps(xmm1, xmm7)
    _mm_and_ps(xmm1, _mm_set1_ps(0x7FFFFFFF))
    _mm_cmpeq_ps(xmm1, _mm_set1_ps(0x7F800000))
    _mm_store_ps(xmm0, xmm4)
    _mm_and_ps(xmm2, xmm0)
    _mm_andnot_ps(xmm0, Pi)
    _mm_or_ps(xmm0, xmm2)
    _mm_cmpeq_ps(xmm7, _mm_set1_ps(0.0))
    _mm_store_ps(xmm2, Pi_2)
    _mm_and_ps(xmm2, xmm7)
    _mm_cmpeq_ps(xmm3, xmm3)
    _mm_andnot_ps(xmm7, xmm3)
    _mm_or_ps(xmm7, xmm2)
    _mm_store_ps(xmm2, xmm6)
    _mm_and_ps(xmm2, _mm_set1_ps(0x7FFFFFFF))
    _mm_cmpeq_ps(xmm2, _mm_set1_ps(0x7F800000))
    _mm_cmpeq_ps(xmm6, _mm_set1_ps(0.0))
    _mm_and_ps(xmm0, xmm6)
    _mm_andnot_ps(xmm6, xmm7)
    _mm_or_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm6)
    _mm_store_ps(xmm0, Pi_4)
    _mm_store_ps(xmm6, xmm4)
    _mm_and_ps(xmm0, xmm6)
    _mm_andnot_ps(xmm6, Pi3_4)
    _mm_or_ps(xmm6, xmm0)
    _mm_and_ps(xmm6, xmm1)
    _mm_andnot_ps(xmm1, Pi_2)
    _mm_or_ps(xmm1, xmm6)
    _mm_and_ps(xmm1, xmm2)
    _mm_andnot_ps(xmm2, xmm7)
    _mm_or_ps(xmm2, xmm1)
    _mm_cmpeq_epi32(xmm3, xmm2)
    _mm_store_ps(xmm1, _mm_set1_ps(-0.0))
    _mm_and_ps(xmm1, xmm4)
    _mm_andnot_ps(xmm4, Pi)
    _mm_or_ps(xmm4, xmm1)
    _mm_add_ps(xmm5, xmm4)
    _mm_and_ps(xmm5, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm3, xmm5)
    _mm_store_ps(xmm0, xmm3)
else
    fld y
    fld x
    fpatan
endif
    ret
    endp

    end
