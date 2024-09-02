; XMVECTORCLAMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorClamp proc XM_CALLCONV V:FXMVECTOR, Min:FXMVECTOR, Max:FXMVECTOR

    _mm_max_ps(xmm0, xmm1)
    _mm_min_ps(xmm0, xmm2)
    ret

XMVectorClamp endp

    end
