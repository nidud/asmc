; XMVECTORMIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorMin proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_min_ps(xmm0, xmm1)
    ret

XMVectorMin endp

    end
