; XMVECTORORINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorOrInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_or_si128(xmm0, xmm1)
    ret

XMVectorOrInt endp

    end
