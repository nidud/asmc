; XMSTORESHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreShort2 proc XM_CALLCONV pDestination:ptr XMSHORT2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ;; Bounds check

    _mm_max_ps(xmm0, _mm_get_epi32(-32767.0, -32767.0, -32767.0, -32767.0))
    _mm_min_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm0)

    ;; Pack the ints into shorts

    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_ss([rcx], _mm_castsi128_ps(xmm0))
    ret

XMStoreShort2 endp

    end
