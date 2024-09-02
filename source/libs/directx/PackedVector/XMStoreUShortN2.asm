; XMSTOREUSHORTN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUShortN2 proc XM_CALLCONV pDestination:ptr XMUSHORTN2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ;; Bounds check

    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm0)

    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory

    movd    edx,xmm0
    mov     [rcx].XMUSHORTN2.x,dx
    shufps  xmm0,xmm0,11100110B
    movd    edx,xmm0
    mov     [rcx].XMUSHORTN2.y,dx
    ret

XMStoreUShortN2 endp

    end
