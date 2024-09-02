; XMSTOREU555.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreU555 proc XM_CALLCONV pDestination:ptr XMU555, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    ;; Bounds check

    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(31.0, 31.0, 31.0, 1.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm1)

    ;; No SSE operations will write to 16-bit values, so we have to extract them manually

    _mm_extract_epi16(xmm1, 0)
    and eax,0x1F
    mov edx,eax
    _mm_extract_epi16(xmm1, 2)
    and eax,0x1F
    shl eax,5
    or  edx,eax
    _mm_extract_epi16(xmm1, 4)
    and eax,0x1F
    shl eax,10
    or  edx,eax
    _mm_extract_epi16(xmm1, 6)
    neg eax
    sbb eax,eax
    and eax,0x8000
    or  edx,eax
    mov [rcx].XMU555.v,dx
    ret

XMStoreU555 endp

    end
