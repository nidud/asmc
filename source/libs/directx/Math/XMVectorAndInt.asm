; XMVECTORANDINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorAndInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_and_ps(xmm0, xmm1)
    ret

XMVectorAndInt endp

    end
