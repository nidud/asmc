; XMLOADUDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUDecN4 proc XM_CALLCONV pSource:ptr XMUDECN4

    ldr rcx,pSource

    ;; Splat the color in all four entries

    _mm_load_ps1([rcx])

    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000

    _mm_and_ps(xmm0, g_XMMaskDec4)

    ;; a is unsigned! Flip the bit to convert the order to signed

    _mm_xor_ps(xmm0, g_XMFlipW)

    ;; Convert to floating point numbers

    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))

    ;; RGB + 0, A + 0x80000000.f to undo the signed order.

    _mm_add_ps(xmm0, g_XMAddUDec4)

    ;; Convert 0-255 to 0.0f-1.0f

    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/1023.0, 1.0/(1023.0*1024.0), 1.0/(1023.0*1024.0*1024.0), 1.0/(3.0*1024.0*1024.0*1024.0)))
    ret

XMLoadUDecN4 endp

    end
