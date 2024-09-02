; XMVECTOREXPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorExpE proc XM_CALLCONV uses xmm6 xmm7 V:FXMVECTOR

    _mm_load_si128(xmm3, g_XMExponentBias)
    _mm_load_si128(xmm4, g_XMInfinity)
    _mm_load_si128(xmm7, g_XMLgE)
    _mm_mul_ps(xmm7, xmm0)
    _mm_cvttps_epi32(xmm3, xmm7)
    _mm_load_si128(xmm1, xmm7)
    _mm_add_pi32(xmm2, xmm3)
    _mm_cvtepi32_ps(xmm0, xmm3)
    _mm_slli_epi32(xmm2, 23)
    _mm_sub_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, g_XMExpEst7)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst6)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst5)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst4)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst3)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst2)
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMExpEst1)
    _mm_mul_ps(xmm0, xmm1)
    _mm_load_si128(xmm1, g_XM253)
    _mm_add_pi32(xmm1, xmm3)
    _mm_slli_epi32(xmm1, 23)
    _mm_add_ps(xmm0, g_XMOne)
    _mm_div_ps(xmm2, xmm0)
    _mm_div_ps( xmm1, xmm0)
    _mm_load_si128(xmm0, g_XMBin128)
    _mm_mul_ps(xmm1, g_XMMinNormal)
    _mm_cmpgt_epi32(xmm0, xmm7)
    _mm_load_si128(xmm6, xmm0)
    _mm_and_si64(xmm0, xmm2)
    _mm_andnot_si64(xmm6, xmm4)
    _mm_or_si64(xmm6, xmm0)
    _mm_load_si128(xmm0, g_XMSubnormalExponent)
    _mm_cmpgt_epi32(xmm0, xmm3)
    _mm_load_si128(xmm3, g_XMQNaNTest)
    _mm_load_si128(xmm5, xmm0)
    _mm_and_si64(xmm3, xmm7)
    _mm_cmpeq_epi32(xmm3, g_XMZero)
    _mm_andnot_si64(xmm0, xmm2)
    _mm_load_si128(xmm2, g_XMNegativeZero)
    _mm_and_si64(xmm5, xmm1)
    _mm_or_si64(xmm5, xmm0)
    _mm_and_si64(xmm2, xmm7)
    _mm_cmpeq_epi32(xmm2, g_XMNegativeZero)
    _mm_load_si128(xmm0, g_XMBinNeg150)
    _mm_cmpgt_epi32(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm0)
    _mm_andnot_si64(xmm0, g_XMZero)
    _mm_or_si64(xmm5, xmm0)
    _mm_load_si128(xmm0, xmm4)
    _mm_and_si64(xmm0, xmm7)
    _mm_and_si64(xmm5, xmm2)
    _mm_cmpeq_epi32(xmm0, xmm4)
    _mm_andnot_si64(xmm3, xmm0)
    _mm_andnot_si64(xmm2, xmm6)
    _mm_load_si128(xmm0, xmm3)
    _mm_and_si64(xmm3, g_XMQNaN)
    _mm_or_si64(xmm5, xmm2)
    _mm_andnot_si64(xmm0, xmm5)
    _mm_or_si64(xmm0, xmm3)
    ret

XMVectorExpE endp

    end
