; XMLOADSHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadShort4 proc XM_CALLCONV pSource:ptr XMSHORT4

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

    ;; Fix y and w because they are 65536 too large

    _mm_mul_ps(xmm0, g_XMFixupY16W16)

    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))
    ret

XMLoadShort4 endp

    end
