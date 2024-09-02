; XMSTORESHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreShortN4 proc XM_CALLCONV pDestination:ptr XMSHORTN4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_max_ps(xmm0, g_XMNegativeOne)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))
    _mm_cvtps_epi32(xmm0)
    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_sd([rcx], _mm_castsi128_pd(xmm0))
    ret

XMStoreShortN4 endp

    end
