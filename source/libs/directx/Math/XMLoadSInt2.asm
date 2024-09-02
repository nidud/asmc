; XMLOADSINT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadSInt2 proc XM_CALLCONV pSource:ptr XMINT2

    ldr rcx,pSource

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_cvtepi32_ps(xmm0)
    ret

XMLoadSInt2 endp

    end
