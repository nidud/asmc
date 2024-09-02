; XMVECTORISNAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorIsNaN proc XM_CALLCONV V:FXMVECTOR

    _mm_cmpneq_ps(xmm0, xmm0)
    ret

XMVectorIsNaN endp

    end
