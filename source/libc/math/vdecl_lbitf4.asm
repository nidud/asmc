; VDECL_LBITF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include immintrin.inc

.code

ifdef __SSE2__

__vdecl_lbitf4 proc __vdecl uses xmm6 xmm7 x:XVECTOR

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, { 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF })
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 4)
    _mm_store_ps(xmm6, xmm1)
    __vdecl_srlf4(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, { 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF })
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 3)
    _mm_store_ps(xmm7, xmm1)
    __vdecl_srlf4(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm6)
    _mm_or_si128(xmm1, xmm7)
    _mm_store_ps(xmm6, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, { 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F })
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 2)
    _mm_store_ps(xmm7, xmm1)
    __vdecl_srlf4(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm6)
    _mm_or_si128(xmm1, xmm7)
    _mm_store_ps(xmm6, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_cmpgt_epi32(xmm1, { 0x00000003, 0x00000003, 0x00000003, 0x00000003 })
    _mm_srli_epi32(xmm1, 31)
    _mm_slli_epi32(xmm1, 1)
    _mm_store_ps(xmm7, xmm1)
    __vdecl_srlf4(xmm0, xmm1)

    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm6)
    _mm_or_si128(xmm0, xmm7)

    _mm_srli_epi32(xmm1, 1)
    _mm_or_si128(xmm0, xmm1)
    ret
    endp
endif
    end
