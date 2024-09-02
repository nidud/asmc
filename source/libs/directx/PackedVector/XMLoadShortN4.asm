; XMLOADSHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadShortN4 proc XM_CALLCONV pSource:ptr XMSHORTN4

    ldr rcx,pSource

    ;; Splat the color in all four entries (x,z,y,w)

    _mm_load1_pd([rcx])

    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000

    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)

    ;; x and z are unsigned! Flip the bits to convert the order to signed

    _mm_xor_ps(xmm0, g_XMFlipX16Y16Z16W16)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; x and z - 0x8000 to complete the conversion

    _mm_add_ps(xmm0, g_XMFixX16Y16Z16W16)

    ;; Convert to -1.0f - 1.0f

    _mm_mul_ps(xmm0, g_XMNormalizeX16Y16Z16W16)

    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))

    ;; Clamp result (for case of -32768)

    _mm_max_ps( xmm0, g_XMNegativeOne )
    ret

XMLoadShortN4 endp

    end
