; XMVECTORDIVIDE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorDivide proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_div_ps(xmm0, xmm1)
    ret

XMVectorDivide endp

    end
