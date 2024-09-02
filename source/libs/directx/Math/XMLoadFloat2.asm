; XMLOADFLOAT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat2 proc XM_CALLCONV pSource:ptr XMFLOAT2

    ldr rcx,pSource

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    ret

XMLoadFloat2 endp

    end
