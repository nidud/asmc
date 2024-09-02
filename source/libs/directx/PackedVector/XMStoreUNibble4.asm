; XMSTOREUNIBBLE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUNibble4 proc XM_CALLCONV pDestination:ptr XMUNIBBLE4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    ;; Bounds check

    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(15.0, 15.0, 15.0, 15.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm1)

    ;; No SSE operations will write to 16-bit values, so we have to extract them manually

    _mm_extract_epi16(xmm1, 0)
    and eax,0xF
    mov edx,eax
    _mm_extract_epi16(xmm1, 2)
    and eax,0xF
    shl eax,4
    or  edx,eax
    _mm_extract_epi16(xmm1, 4)
    and eax,0xF
    shl eax,8
    or  edx,eax
    _mm_extract_epi16(xmm1, 6)
    and eax,0xF
    shl eax,12
    or  edx,eax
    mov [rcx],dx
    ret

XMStoreUNibble4 endp

    end
