; XMVECTORANDCINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorAndCInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_andnot_si128(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm1)
    ret

XMVectorAndCInt endp

    end
