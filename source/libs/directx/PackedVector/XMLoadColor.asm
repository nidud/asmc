; XMLOADCOLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadColor proc XM_CALLCONV pSource:ptr XMCOLOR

    ldr rcx,pSource

    ;; Splat the color in all four entries

    movd xmm0,[rcx]
    XM_PERMUTE_PS()

    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000

    _mm_and_si128(xmm0, g_XMMaskA8R8G8B8)

    ;; a is unsigned! Flip the bit to convert the order to signed

    _mm_xor_si128(xmm0, g_XMFlipA8R8G8B8)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(xmm0)

    ;; RGB + 0, A + 0x80000000.f to undo the signed order.

    _mm_add_ps(xmm0, g_XMFixAA8R8G8B8)

    ;; Convert 0-255 to 0.0f-1.0f

    _mm_mul_ps(xmm0, g_XMNormalizeA8R8G8B8)
    ret

XMLoadColor endp

    end
