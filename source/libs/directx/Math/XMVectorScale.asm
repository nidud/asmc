; XMVECTORSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorScale proc XM_CALLCONV V:FXMVECTOR, ScaleFactor:float

    _mm_set_ps1(xmm1)
    _mm_mul_ps(xmm0, xmm1)
    ret

XMVectorScale endp

    end
