; XMLOADUSHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUShortN4 proc XM_CALLCONV pSource:ptr XMUSHORTN4

    ldr rcx,pSource

    ;; Splat the color in all four entries (x,z,y,w)

    _mm_load1_pd([rcx])

    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000

    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)

    ;; y and w are signed! Flip the bits to convert the order to unsigned

    _mm_xor_ps(xmm0, g_XMFlipZW)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; y and w + 0x8000 to complete the conversion

    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 0.0, 32768.0*65536.0, 32768.0*65536.0))

    ;; Fix y and w because they are 65536 too large

    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/65535.0, 1.0/65535.0, 1.0/(65535.0*65536.0), 1.0/(65535.0*65536.0)))

    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))
    ret

XMLoadUShortN4 endp

    end
