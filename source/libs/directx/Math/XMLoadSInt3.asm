; XMLOADSINT3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadSInt3 proc XM_CALLCONV pSource:ptr XMINT3

    ldr rcx,pSource

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_load_ss(xmm2, [rcx+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ret

XMLoadSInt3 endp

    end
