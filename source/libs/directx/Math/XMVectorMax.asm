; XMVECTORMAX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorMax proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_max_ps(xmm0, xmm1)
    ret

XMVectorMax endp

    end
