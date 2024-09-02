; XMSTOREXDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreXDecN4 proc XM_CALLCONV pDestination:ptr XMXDECN4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ; XMXDECN4

    _mm_max_ps(xmm0, _mm_get_epi32(-1.0, -1.0, -1.0, 0.0))
    _mm_min_ps(xmm0, g_XMOne)

    ;; Scale by multiplication

    _mm_mul_ps(xmm0, _mm_get_epi32(511.0, 511.0*1024.0, 511.0*1048576.0, 3.0*536870912.0))

    ;; Convert to int (W is unsigned)

    _mm_cvtps_epi32(xmm0)

    ;; Mask off any fraction

    _mm_and_si128(xmm0, _mm_get_epi32(0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 29))

    ;; To fix W, add itself to shift it up to <<30 instead of <<29

    _mm_and_si128(_mm_store_ps(xmm1, xmm0), g_XMMaskW)
    _mm_add_epi32(xmm0, xmm1)

    ;; Do a horizontal or of all 4 entries

    _mm_store_ps(xmm1, xmm0)
    XM_PERMUTE_PS(_mm_castsi128_ps(xmm1), _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    _mm_store_ss([rcx], _mm_castsi128_ps(xmm0))
    ret

XMStoreXDecN4 endp

    end
