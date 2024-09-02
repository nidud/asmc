; XMVECTORSELECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSelect proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, Control:FXMVECTOR

    _mm_and_ps(xmm1, xmm2)
    _mm_andnot_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm2)
    ret

XMVectorSelect endp

    end
