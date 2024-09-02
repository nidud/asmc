; XMVECTORGREATER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGreater proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_cmpgt_ps(xmm1, xmm0, xmm1)
    _mm_store_ps(xmm0, xmm1)
    ret

XMVectorGreater endp

    end
