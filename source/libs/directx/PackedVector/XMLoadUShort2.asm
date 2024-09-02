; XMLOADUSHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUShort2 proc XM_CALLCONV pSource:ptr XMUSHORT2

    ldr rcx,pSource

    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)

    _mm_load_ps1([rcx])

    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0

    _mm_and_ps(xmm0, g_XMMaskX16Y16)

    ;; y needs to be sign flipped

    _mm_xor_ps(xmm0, g_XMFlipY)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; Y is 65536 times too large

    _mm_mul_ps(xmm0, g_XMFixupY16)

    ;; y + 0x8000 to undo the signed order.

    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 32768.0, 0.0, 0.0))
    ret

XMLoadUShort2 endp

    end
