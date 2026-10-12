; LOG2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc

    option comdat:on

    define C1 -7.21242E-01
    define C2 +4.79384E-01
    define C3 -3.50295E-01
    define C4 +2.48590E-01
    define C5 -1.45700E-01
    define C6 +5.71480E-02
    define C7 -1.05780E-02

    assume uses xmm6 xmm7
endif

.code

log2f proc x:float
ifdef _WIN64

  local exponentSub:XMVECTOR

    _mm_store_ps(xmm6, xmm0)

    _mm_and_si128(_mm_store_ps(xmm7, _mm_set1_ps(0x007FFFFF)), xmm0)
    __vdecl_lbitf4(xmm7)

    _mm_sub_epi32(_mm_store_ps(xmm1, _mm_set1_ps(23)), xmm0)
    _mm_sub_epi32(_mm_store_ps(xmm0, _mm_set1_ps(-126)), xmm1)
    _mm_store_ps(exponentSub, xmm0)
    __vdecl_sllf4(xmm7, xmm1)
    _mm_and_si128(xmm0, _mm_set1_ps(0x007FFFFF))

    _mm_and_si128(_mm_store_ps(xmm1, xmm6), _mm_set1_ps(0x7F800000))
    _mm_store_ps(xmm5, xmm1)
    _mm_cmpeq_epi32(xmm1, _mm_set1_ps(0.0))
    _mm_and_si128(_mm_store_ps(xmm2, xmm1), exponentSub)
    _mm_sub_epi32(_mm_srli_epi32(xmm5, 23), _mm_set1_ps(127))
    _mm_andnot_si128(_mm_store_ps(xmm3, xmm1), xmm5)

    _mm_or_si128(xmm2, xmm3)
    _mm_and_si128(xmm0, xmm1)
    _mm_andnot_si128(xmm1, xmm7)
    _mm_or_si128(xmm0, xmm1)
    _mm_or_si128(xmm0, _mm_set1_ps(1.0))
    _mm_sub_ps(xmm0, _mm_set1_ps(1.0))
    _mm_store_ps(xmm1, xmm0)

    _mm_mul_ps(xmm0, _mm_set1_ps(C7))
    _mm_add_ps(xmm0, _mm_set1_ps(C6))

    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C5))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C4))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C3))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C2))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(C1))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_set1_ps(M_LOG2E))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_cvtepi32_ps(xmm2))

    _mm_store_ps(xmm1, xmm6)
    _mm_and_si128(xmm1, _mm_set1_ps(0x7FFFFFFF))
    _mm_cmpeq_epi32(xmm1, _mm_set1_ps(0x7F800000))

    _mm_store_ps(xmm2, xmm6)
    _mm_store_ps(xmm3, xmm6)

    _mm_cmpgt_epi32(xmm2, _mm_set1_ps(0.0))
    _mm_cmpgt_epi32(xmm3, _mm_set1_ps(0x7F800000))
    _mm_andnot_si128(xmm3, xmm2)

    _mm_store_ps(xmm2, xmm6)
    _mm_and_si128(xmm2, _mm_set1_ps(0x7FFFFFFF))
    _mm_cmpeq_epi32(xmm2, _mm_set1_ps(0.0))

    _mm_store_ps(xmm4, xmm6)
    _mm_and_si128(xmm4, _mm_set1_ps(0x007FFFFF))
    _mm_and_si128(xmm6, _mm_set1_ps(0x7F800000))
    _mm_cmpeq_epi32(xmm4, _mm_set1_ps(0.0))
    _mm_cmpeq_epi32(xmm6, _mm_set1_ps(0x7F800000))
    _mm_andnot_si128(xmm4, xmm6)

    _mm_store_ps(xmm5, xmm1)
    _mm_and_si128(xmm5, _mm_set1_ps(0x7F800000))
    _mm_andnot_si128(xmm1, xmm0)
    _mm_or_si128(xmm5, xmm1)

    _mm_store_ps(xmm0, xmm2)
    _mm_and_si128(xmm0, _mm_set1_ps(0xFF800000))
    _mm_andnot_si128(xmm2, _mm_set1_ps(0xFFC00000))
    _mm_or_si128(xmm0, xmm2)

    _mm_store_ps(xmm2, xmm3)
    _mm_and_si128(xmm2, xmm5)
    _mm_andnot_si128(xmm3, xmm0)
    _mm_or_si128(xmm2, xmm3)

    _mm_store_ps(xmm0, xmm4)
    _mm_and_si128(xmm0, _mm_set1_ps(0x7FC00000))
    _mm_andnot_si128(xmm4, xmm2)
    _mm_or_si128(xmm0, xmm4)
else
    fld1
    fld     x
    fyl2x
endif
    ret
    endp

    end
