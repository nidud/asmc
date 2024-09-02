; XMVECTORMULTIPLYADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorMultiplyAdd proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, V3:FXMVECTOR

    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, xmm2)
    ret

XMVectorMultiplyAdd endp

    end
