; VDECL_LOG2F4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include immintrin.inc

.code

ifdef __SSE2__

__vdecl_log2f4 proc __vdecl uses xmm6 xmm7 x:XVECTOR

  local exponentSub:XMVECTOR

    _mm_store_ps(xmm6, xmm0)

    _mm_and_si128(_mm_store_ps(xmm7, g_X4IQNANTEST), xmm0)
    __vdecl_lbitf4(xmm7)

    _mm_sub_epi32(_mm_store_ps(xmm1, g_X4I23), xmm0)
    _mm_sub_epi32(_mm_store_ps(xmm0, g_X4ISUBNEXP), xmm1)
    _mm_store_ps(exponentSub, xmm0)
    __vdecl_sllf4(xmm7, xmm1)
    _mm_and_si128(xmm0, g_X4IQNANTEST)

    _mm_and_si128(_mm_store_ps(xmm1, xmm6), g_X4IINFINITY)
    _mm_store_ps(xmm5, xmm1)
    _mm_cmpeq_epi32(xmm1, g_X4FZERO)
    _mm_and_si128(_mm_store_ps(xmm2, xmm1), exponentSub)
    _mm_sub_epi32(_mm_srli_epi32(xmm5, 23), g_X4IEXPBIAS)
    _mm_andnot_si128(_mm_store_ps(xmm3, xmm1), xmm5)

    _mm_or_si128(xmm2, xmm3)
    _mm_and_si128(xmm0, xmm1)
    _mm_andnot_si128(xmm1, xmm7)
    _mm_or_si128(xmm0, xmm1)
    _mm_or_si128(xmm0, g_X4FONE)
    _mm_sub_ps(xmm0, g_X4FONE)
    _mm_store_ps(xmm1, xmm0)

    _mm_mul_ps(xmm0, g_X4FLOGEST7)
    _mm_add_ps(xmm0, g_X4FLOGEST6)

    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST5)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST4)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST3)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST2)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST1)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_X4FLOGEST0)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_cvtepi32_ps(xmm2))

    _mm_store_ps(xmm1, xmm6)
    _mm_and_si128(xmm1, g_X4IABSMASK)
    _mm_cmpeq_epi32(xmm1, g_X4IINFINITY)

    _mm_store_ps(xmm2, xmm6)
    _mm_store_ps(xmm3, xmm6)

    _mm_cmpgt_epi32(xmm2, g_X4FZERO)
    _mm_cmpgt_epi32(xmm3, g_X4IINFINITY)
    _mm_andnot_si128(xmm3, xmm2)

    _mm_store_ps(xmm2, xmm6)
    _mm_and_si128(xmm2, g_X4IABSMASK)
    _mm_cmpeq_epi32(xmm2, g_X4FZERO)

    _mm_store_ps(xmm4, xmm6)
    _mm_and_si128(xmm4, g_X4IQNANTEST)
    _mm_and_si128(xmm6, g_X4IINFINITY)
    _mm_cmpeq_epi32(xmm4, g_X4FZERO)
    _mm_cmpeq_epi32(xmm6, g_X4IINFINITY)
    _mm_andnot_si128(xmm4, xmm6)

    _mm_store_ps(xmm5, xmm1)
    _mm_and_si128(xmm5, g_X4IINFINITY)
    _mm_andnot_si128(xmm1, xmm0)
    _mm_or_si128(xmm5, xmm1)

    _mm_store_ps(xmm0, xmm2)
    _mm_and_si128(xmm0, g_X4INEGINF)
    _mm_andnot_si128(xmm2, g_X4INAN)
    _mm_or_si128(xmm0, xmm2)

    _mm_store_ps(xmm2, xmm3)
    _mm_and_si128(xmm2, xmm5)
    _mm_andnot_si128(xmm3, xmm0)
    _mm_or_si128(xmm2, xmm3)

    _mm_store_ps(xmm0, xmm4)
    _mm_and_si128(xmm0, g_X4IQNAN)
    _mm_andnot_si128(xmm4, xmm2)
    _mm_or_si128(xmm0, xmm4)
    ret
    endp
endif
    end
