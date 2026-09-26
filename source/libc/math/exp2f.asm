; EXP2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc

define g_X4FEXPEST1     <{ -6.93147182e-1, -6.93147182e-1, -6.93147182e-1, -6.93147182e-1 }>
define g_X4FEXPEST2     <{ +2.40226462e-1, +2.40226462e-1, +2.40226462e-1, +2.40226462e-1 }>
define g_X4FEXPEST3     <{ -5.55036440e-2, -5.55036440e-2, -5.55036440e-2, -5.55036440e-2 }>
define g_X4FEXPEST4     <{ +9.61597636e-3, +9.61597636e-3, +9.61597636e-3, +9.61597636e-3 }>
define g_X4FEXPEST5     <{ -1.32823968e-3, -1.32823968e-3, -1.32823968e-3, -1.32823968e-3 }>
define g_X4FEXPEST6     <{ +1.47491097e-4, +1.47491097e-4, +1.47491097e-4, +1.47491097e-4 }>
define g_X4FEXPEST7     <{ -1.08635004e-5, -1.08635004e-5, -1.08635004e-5, -1.08635004e-5 }>
define g_X4I128         <{ 0x43000000, 0x43000000, 0x43000000, 0x43000000 }>
define g_X4IMINNORM     <{ 0x00800000, 0x00800000, 0x00800000, 0x00800000 }>
define g_X4INEG150      <{ 0xC3160000, 0xC3160000, 0xC3160000, 0xC3160000 }>
define g_X4I253         <{ 253, 253, 253, 253 }>

undef __vdecl_exp2f4
alias <__vdecl_exp2f4>=<exp2f>
assume uses xmm6 xmm7
endif

.code

exp2f proc x:float
ifdef _WIN64
    _mm_load_si128(xmm2, xmm0)
    _mm_cvttps_epi32(xmm5, xmm0)
    _mm_cvtepi32_ps(xmm1, xmm5)
    _mm_sub_ps(xmm2, xmm1)
    _mm_mul_ps(_mm_load_si128(xmm3, g_X4FEXPEST7), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST6), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST5), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST4), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST3), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST2), xmm2)
    _mm_mul_ps(_mm_add_ps(xmm3, g_X4FEXPEST1), xmm2)
    _mm_load_si128(xmm2, g_X4IEXPBIAS)
    _mm_add_pi32(xmm2, xmm5)
    _mm_slli_epi32(xmm2, 23)
    _mm_add_ps(xmm3, g_X4FONE)
    _mm_div_ps(xmm2, xmm3)
    _mm_load_si128(xmm1, g_X4I253)
    _m_paddd(xmm1, xmm5)
    _mm_slli_epi32(xmm1, 23)
    _mm_div_ps(xmm1, xmm3)
    _mm_mul_ps(xmm1, g_X4IMINNORM)
    _mm_load_si128(xmm7, xmm0)
    _mm_load_si128(xmm0, g_X4I128)
    _mm_cmpgt_epi32(xmm0, xmm7)
    _mm_load_si128(xmm6, xmm0)
    _mm_and_si64(xmm0, xmm2)
    _mm_load_si128(xmm4, g_X4IINFINITY)
    _mm_andnot_si64(xmm6, xmm4)
    _mm_or_si64(xmm6, xmm0)
    _mm_load_si128(xmm3, g_X4IQNANTEST)
    _mm_and_si64(xmm3, xmm7)
    _mm_cmpeq_epi32(xmm3, g_X4FZERO)
    _mm_load_si128(xmm0, g_X4ISUBNEXP)
    _mm_cmpgt_epi32(xmm0, xmm5)
    _mm_load_si128(xmm5, xmm0)
    _mm_andnot_si64(xmm0, xmm2)
    _mm_load_si128(xmm2, g_X4FNEGZERO)
    _mm_and_si64(xmm5, xmm1)
    _mm_or_si64(xmm5, xmm0)
    _mm_and_si64(xmm2, xmm7)
    _mm_cmpeq_epi32(xmm2, g_X4FNEGZERO)
    _mm_load_si128(xmm0, g_X4INEG150)
    _mm_cmplt_epi32(xmm0, xmm7, xmm0)
    _mm_and_si64(xmm5, xmm0)
    _mm_andnot_si64(xmm0, g_X4FZERO)
    _mm_or_si64(xmm5, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_and_si64(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm2)
    _mm_cmpeq_epi32(xmm0, xmm4)
    _mm_andnot_si64(xmm3, xmm0)
    _mm_andnot_si64(xmm2, xmm6)
    _mm_load_si128(xmm0, xmm3)
    _mm_and_si64(xmm3, g_X4IQNAN)
    _mm_or_si64(xmm5, xmm2)
    _mm_andnot_si64(xmm0, xmm5)
    _mm_or_si64(xmm0, xmm3)
else
    powf(2.0, x)
endif
    ret
    endp

    end
