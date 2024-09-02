; XMLOADUBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUByteN4 proc XM_CALLCONV pSource:ptr XMUBYTEN4

    ldr rcx,pSource

    ;; Splat the color in all four entries (x,z,y,w)

    _mm_load1_ps([rcx])

    ;; Mask x&0ff,y&0xff00,z&0xff0000,w&0xff000000

    _mm_and_ps(xmm0, g_XMMaskByte4)

    ;; w is signed! Flip the bits to convert the order to unsigned

    _mm_xor_ps(xmm0, g_XMFlipW)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; w + 0x80 to complete the conversion

    _mm_add_ps(xmm0, g_XMAddUDec4)

    ;; Fix y, z and w because they are too large

    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/255.0, 1.0/(255.0*256.0), 1.0/(255.0*65536.0), 1.0/(255.0*65536.0*256.0)))
    ret

XMLoadUByteN4 endp

    end
