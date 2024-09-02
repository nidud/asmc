; XMSTOREDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreDecN4 proc XM_CALLCONV pDestination:ptr XMDECN4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    ;; Clamp to bounds

    _mm_max_ps(xmm1, g_XMNegativeOne)
    _mm_min_ps(xmm1, g_XMOne)

    ;; Scale by multiplication

    _mm_mul_ps(xmm1, _mm_get_epi32(511.0, 511.0*1024.0, 511.0*1024.0*1024.0, 1.0*1024.0*1024.0*1024.0))

    ;; Convert to int

    _mm_cvttps_epi32(xmm1)

    ;; Mask off any fraction

    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 30))

    ;; Do a horizontal or of 4 entries

    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))

    ;; x = x|z, y = y|w

    _mm_or_si128(xmm1, xmm0)

    ;; Move Z to the x position

    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))

    ;; i = x|y|z|w

    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss([rcx], _mm_castsi128_ps(xmm0))
    ret

XMStoreDecN4 endp

    end
