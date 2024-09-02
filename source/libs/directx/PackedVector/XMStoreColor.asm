; XMSTORECOLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreColor proc XM_CALLCONV pDestination:ptr XMCOLOR, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ;; Set <0 to 0

    _mm_max_ps(xmm0, g_XMZero)

    ;; Set>1 to 1

    _mm_min_ps(xmm0, g_XMOne)

    ;; Convert to 0-255

    _mm_mul_ps(xmm0, _mm_get_epi32(255.0, 255.0, 255.0, 255.0))

    ;; Shuffle RGBA to ARGB

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))

    ;; Convert to int

    _mm_cvtps_epi32(xmm0)

    ;; Mash to shorts

    _mm_packs_epi32(xmm0, xmm0)

    ;; Mash to bytes

    _mm_packus_epi16(xmm0, xmm0)

    ;; Store the color

    _mm_store_ss([rcx], _mm_castsi128_ps(xmm0))
    ret

XMStoreColor endp

    end
