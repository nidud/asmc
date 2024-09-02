; XMLOADSHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadShort2 proc XM_CALLCONV pSource:ptr XMSHORT2

    ldr rcx,pSource

    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)

    _mm_load_ps1([rcx])

    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0

    _mm_and_ps(xmm0, g_XMMaskX16Y16)

    ;; x needs to be sign extended

    _mm_xor_ps(xmm0, g_XMFlipX16Y16)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; x - 0x8000 to undo the signed order.

    _mm_add_ps(xmm0, g_XMFixX16Y16)

    ;; Convert -1.0f - 1.0f

    _mm_mul_ps(xmm0, g_XMNormalizeX16Y16)

    ;; Clamp result (for case of -32768)

    _mm_max_ps( xmm0, g_XMNegativeOne )
    ret

XMLoadShort2 endp

    end
