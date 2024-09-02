; XMVECTOREQUALINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorEqualInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_cmpeq_epi32(xmm0, xmm1)
    ret

XMVectorEqualInt endp

    end
