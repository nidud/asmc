; VDECL_EXP22.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include intrin.inc

define g_X2FZERO        <{ 0.0, 0.0 }>
define g_X2FNEGZERO     <{-0.0,-0.0 }>

.code

ifdef __SSE2__

__vdecl_exp22 proc __vdecl uses xmm6 xmm7 x:XVECTOR

    _mm_load_si128(xmm2, xmm0)
    _mm_cvttpd_epi32(xmm5, xmm0)
    _mm_cvtepi32_pd(xmm1, xmm5)
    _mm_sub_pd(xmm2, xmm1)
    _mm_mul_pd(_mm_load_si128(xmm3, { -1.08635004e-5, -1.08635004e-5 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { +1.47491097e-4, +1.47491097e-4 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { -1.32823968e-3, -1.32823968e-3 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { +9.61597636e-3, +9.61597636e-3 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { -5.55036440e-2, -5.55036440e-2 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { +2.40226462e-1, +2.40226462e-1 }), xmm2)
    _mm_mul_pd(_mm_add_pd(xmm3, { -6.93147182e-1, -6.93147182e-1 }), xmm2)
    _mm_load_si128(xmm2, { 0x3FF, 0x3FF })
    _mm_add_epi64(xmm2, xmm5)
    _mm_slli_epi64(xmm2, 52)
    _mm_add_pd(xmm3, g_X2FONE)
    _mm_div_pd(xmm2, xmm3)
    _mm_load_si128(xmm1, { 1149, 1149 })
    _mm_add_epi64(xmm1, xmm5)
    _mm_slli_epi64(xmm1, 52)
    _mm_div_pd(xmm1, xmm3)
    _mm_mul_pd(xmm1, { 0x0010000000000000, 0x0010000000000000 })
    _mm_load_si128(xmm7, xmm0)
    _mm_load_si128(xmm0, { 128.0, 128.0 })
    _mm_cmpgt_epi64(xmm0, xmm7)
    _mm_load_si128(xmm6, xmm0)
    _mm_and_si64(xmm0, xmm2)
    _mm_load_si128(xmm4, { 0x7FF0000000000000, 0x7FF0000000000000 })
    _mm_andnot_si64(xmm6, xmm4)
    _mm_or_si64(xmm6, xmm0)
    _mm_load_si128(xmm3, { 0x000FFFFFFFFFFFFF, 0x000FFFFFFFFFFFFF })
    _mm_and_si64(xmm3, xmm7)
    _mm_cmpeq_epi64(xmm3, g_X2FZERO)
    _mm_load_si128(xmm0, { -1021, -1021 })
    _mm_cmpgt_epi64(xmm0, xmm5)
    _mm_load_si128(xmm5, xmm0)
    _mm_andnot_si64(xmm0, xmm2)
    _mm_load_si128(xmm2, g_X2FNEGZERO)
    _mm_and_si64(xmm5, xmm1)
    _mm_or_si64(xmm5, xmm0)
    _mm_and_si64(xmm2, xmm7)
    _mm_cmpeq_epi64(xmm2, g_X2FNEGZERO)
    _mm_load_si128(xmm0, { -150.0, -150.0 })
    _mm_cmplt_epi64(xmm0, xmm7, xmm0)
    _mm_and_si64(xmm5, xmm0)
    _mm_andnot_si64(xmm0, g_X2FZERO)
    _mm_or_si64(xmm5, xmm0)
    _mm_store_pd(xmm0, xmm4)
    _mm_and_si64(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm2)
    _mm_cmpeq_epi64(xmm0, xmm4)
    _mm_andnot_si64(xmm3, xmm0)
    _mm_andnot_si64(xmm2, xmm6)
    _mm_load_si128(xmm0, xmm3)
    _mm_and_si64(xmm3, { 0x7FF8000000000000, 0x7FF8000000000000 })
    _mm_or_si64(xmm5, xmm2)
    _mm_andnot_si64(xmm0, xmm5)
    _mm_or_si64(xmm0, xmm3)
    ret
    endp
endif
    end
