; __VDECL_EXP2F4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef __SSE2__
include intrin.inc

    option comdat:on

    define C1 -6.93147182e-1
    define C2 +2.40226462e-1
    define C3 -5.55036440e-2
    define C4 +9.61597636e-3
    define C5 -1.32823968e-3
    define C6 +1.47491097e-4
    define C7 -1.08635004e-5

    assume uses xmm6 xmm7
endif

.code

ifdef __SSE2__

__vdecl_exp2f4 proc __vdecl x:XVECTOR
    _mm_load_si128(xmm2, xmm0)
    _mm_cvttps_epi32(xmm5, xmm0)
    _mm_cvtepi32_ps(xmm1, xmm5)
    _mm_sub_ps(xmm2, xmm1)
    _mm_mul_ps(_mm_load_si128(xmm3, _mm_set1_ps(C7)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C6)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C5)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C4)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C3)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C2)), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, _mm_set1_ps(C1)), xmm2)
    _mm_load_si128(xmm2, _mm_set1_ps(127))
    _mm_add_pi32(xmm2, xmm5)
    _mm_slli_epi32(xmm2, 23)
    _mm_add_ps(xmm3, _mm_set1_ps(1.0))
    _mm_div_ps(xmm2, xmm3)
    _mm_load_si128(xmm1, _mm_set1_ps(253))
    _m_paddd(xmm1, xmm5)
    _mm_slli_epi32(xmm1, 23)
    _mm_div_ps(xmm1, xmm3)
    _mm_mul_ps(xmm1, _mm_set1_ps(0x00800000))
    _mm_load_si128(xmm7, xmm0)
    _mm_load_si128(xmm0, _mm_set1_ps(0x43000000))
    _mm_cmpgt_epi32(xmm0, xmm7)
    _mm_load_si128(xmm6, xmm0)
    _mm_and_si64(xmm0, xmm2)
    _mm_load_si128(xmm4, _mm_set1_ps(0x7F800000))
    _mm_andnot_si64(xmm6, xmm4)
    _mm_or_si64(xmm6, xmm0)
    _mm_load_si128(xmm3, _mm_set1_ps(0x007FFFFF))
    _mm_and_si64(xmm3, xmm7)
    _mm_cmpeq_epi32(xmm3, _mm_set1_ps(0.0))
    _mm_load_si128(xmm0, _mm_set1_ps(-126))
    _mm_cmpgt_epi32(xmm0, xmm5)
    _mm_load_si128(xmm5, xmm0)
    _mm_andnot_si64(xmm0, xmm2)
    _mm_load_si128(xmm2, _mm_set1_ps(-0.0))
    _mm_and_si64(xmm5, xmm1)
    _mm_or_si64(xmm5, xmm0)
    _mm_and_si64(xmm2, xmm7)
    _mm_cmpeq_epi32(xmm2, _mm_set1_ps(-0.0))
    _mm_load_si128(xmm0, _mm_set1_ps(0xC3160000))
    _mm_cmplt_epi32(xmm0, xmm7, xmm0)
    _mm_and_si64(xmm5, xmm0)
    _mm_andnot_si64(xmm0, _mm_set1_ps(0.0))
    _mm_or_si64(xmm5, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_and_si64(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm2)
    _mm_cmpeq_epi32(xmm0, xmm4)
    _mm_andnot_si64(xmm3, xmm0)
    _mm_andnot_si64(xmm2, xmm6)
    _mm_load_si128(xmm0, xmm3)
    _mm_and_si64(xmm3, _mm_set1_ps(0x7FC00000))
    _mm_or_si64(xmm5, xmm2)
    _mm_andnot_si64(xmm0, xmm5)
    _mm_or_si64(xmm0, xmm3)
    ret
    endp
endif
    end
