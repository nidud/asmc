; XMSTOREUBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUByteN4 proc XM_CALLCONV pDestination:ptr XMUBYTEN4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    ;; Clamp to bounds

    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, g_XMOne)

    ;; Scale by multiplication

    _mm_mul_ps(xmm1, _mm_get_epi32(255.0, 255.0*256.0*0.5, 255.0*256.0*256.0, 255.0*256.0*256.0*256.0*0.5))

    ;; Convert to int

    _mm_cvttps_epi32(xmm1)

    ;; Mask off any fraction

    _mm_and_si128(xmm1, _mm_get_epi32(0xFF, 0xFF shl (8-1), 0xFF shl 16, 0xFF shl (24-1)))

    ;; Do a horizontal or of 4 entries

    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(3,2,3,2))

    ;; x = x|z, y = y|w

    _mm_or_si128(xmm1, xmm0)

    ;; Move Z to the x position

    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(1,1,1,1))

    ;; Perform a single bit left shift to fix y|w

    _mm_add_epi32(xmm0, xmm0)

    ;; i = x|y|z|w

    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss([rcx], _mm_castsi128_ps(xmm0))
    ret

XMStoreUByteN4 endp

    end
