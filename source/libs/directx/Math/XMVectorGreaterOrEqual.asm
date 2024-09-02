; XMVECTORGREATEROREQUAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGreaterOrEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_cmpge_ps(xmm1, xmm0, xmm1)
    _mm_store_ps(xmm0, xmm1)
    ret

XMVectorGreaterOrEqual endp

    end
