; __VDECL_EXP22.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include intrin.inc

.code

ifdef __SSE2__

    option comdat:on

    define C1 -1.08635004e-5
    define C2 +1.47491097e-4
    define C3 -1.32823968e-3
    define C4 +9.61597636e-3
    define C5 -5.55036440e-2
    define C6 +2.40226462e-1
    define C7 -6.93147182e-1

__vdecl_exp22 proc __vdecl uses xmm6 xmm7 x:XVECTOR

    _mm_load_si128(xmm2, xmm0)
    _mm_cvttpd_epi32(xmm5, xmm0)
    _mm_cvtepi32_pd(xmm1, xmm5)
    _mm_sub_pd(xmm2, xmm1)
    _mm_mul_pd(_mm_mov_pd(xmm3, _mm_set1_pd(C1)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C2)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C3)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C4)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C5)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C6)), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, _mm_set1_pd(C7)), xmm2)
    _mm_load_si128(xmm2, _mm_set1_pd(0x3FF))
    _mm_add_epi64(xmm2, xmm5)
    _mm_slli_epi64(xmm2, 52)
    _mm_add_pd(xmm3, _mm_set1_pd(1.0))
    _mm_div_pd(xmm2, xmm3)
    _mm_load_si128(xmm1, _mm_set1_pd(1149))
    _mm_add_epi64(xmm1, xmm5)
    _mm_slli_epi64(xmm1, 52)
    _mm_div_pd(xmm1, xmm3)
    _mm_mul_pd(xmm1, _mm_set1_pd(0x1.0p-1022))
    _mm_load_si128(xmm7, xmm0)
    _mm_load_si128(xmm0, _mm_set1_pd(128.0))
    _mm_cmpgt_epi64(xmm0, xmm7)
    _mm_load_si128(xmm6, xmm0)
    _mm_and_si64(xmm0, xmm2)
    _mm_load_si128(xmm4, _mm_set1_pd(0x7FF0000000000000))
    _mm_andnot_si64(xmm6, xmm4)
    _mm_or_si64(xmm6, xmm0)
    _mm_load_si128(xmm3, _mm_set1_pd(0x000FFFFFFFFFFFFF))
    _mm_and_si64(xmm3, xmm7)
    _mm_cmpeq_epi64(xmm3, _mm_set1_pd(0.0))
    _mm_load_si128(xmm0, _mm_set1_pd(-1021))
    _mm_cmpgt_epi64(xmm0, xmm5)
    _mm_load_si128(xmm5, xmm0)
    _mm_andnot_si64(xmm0, xmm2)
    _mm_load_si128(xmm2, _mm_set1_pd(-1.0))
    _mm_and_si64(xmm5, xmm1)
    _mm_or_si64(xmm5, xmm0)
    _mm_and_si64(xmm2, xmm7)
    _mm_cmpeq_epi64(xmm2, _mm_set1_pd(-1.0))
    _mm_load_si128(xmm0, _mm_set1_pd(-150.0))
    _mm_cmplt_epi64(xmm0, xmm7, xmm0)
    _mm_and_si64(xmm5, xmm0)
    _mm_andnot_si64(xmm0, _mm_set1_pd(0.0))
    _mm_or_si64(xmm5, xmm0)
    _mm_store_pd(xmm0, xmm4)
    _mm_and_si64(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm2)
    _mm_cmpeq_epi64(xmm0, xmm4)
    _mm_andnot_si64(xmm3, xmm0)
    _mm_andnot_si64(xmm2, xmm6)
    _mm_load_si128(xmm0, xmm3)
    _mm_and_si64(xmm3, _mm_set1_pd(0x7FF8000000000000))
    _mm_or_si64(xmm5, xmm2)
    _mm_andnot_si64(xmm0, xmm5)
    _mm_or_si64(xmm0, xmm3)
    ret
    endp
endif
    end
