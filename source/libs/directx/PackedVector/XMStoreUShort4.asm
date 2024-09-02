; XMSTOREUSHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUShort4 proc XM_CALLCONV pDestination:ptr XMUSHORT4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ;; Bounds check

    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm0)

    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory

    mov [rcx].XMUSHORT4.x,_mm_extract_epi16(xmm0, 0)
    mov [rcx].XMUSHORT4.y,_mm_extract_epi16(xmm0, 2)
    mov [rcx].XMUSHORT4.z,_mm_extract_epi16(xmm0, 4)
    mov [rcx].XMUSHORT4.w,_mm_extract_epi16(xmm0, 6)
    ret

XMStoreUShort4 endp

    end
