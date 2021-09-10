; XMVECTOR_GETLEADINGBIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVECTOR_GetLeadingBit proc vectorcall this:XMVECTOR

  local r:XMVECTOR, s:XMVECTOR

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, _mm_get_epi32(0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF))
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 4)
    _mm_store_ps(r, xmm1)
    XMVECTOR::multi_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, _mm_get_epi32(0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF))
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 3)
    _mm_store_ps(s, xmm1)
    XMVECTOR::multi_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm1, r)
    _mm_or_si128(xmm1, s)
    _mm_store_ps(r, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, _mm_get_epi32(0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F))
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 2)
    _mm_store_ps(s, xmm1)
    XMVECTOR::multi_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm1, r)
    _mm_or_si128(xmm1, s)
    _mm_store_ps(r, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, _mm_get_epi32(0x00000003, 0x00000003, 0x00000003, 0x00000003))
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 1)
    _mm_store_ps(s, xmm1)
    XMVECTOR::multi_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, r)
    _mm_or_si128(xmm0, s)

    _mm_srli_epi32(xmm1, 1)
    _mm_or_si128(xmm0, xmm1)
    ret

XMVECTOR::GetLeadingBit endp

    end
