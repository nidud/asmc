; XMVECTORNEGATIVEMULTIPLYSUBTRACT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorNegativeMultiplySubtract proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, V3:FXMVECTOR

    _mm_mul_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm2)
    _mm_sub_ps(xmm0, xmm1)
    ret

XMVectorNegativeMultiplySubtract endp

    end
