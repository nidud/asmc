; XMVECTORSETX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetX proc XM_CALLCONV V:FXMVECTOR, x:float

    _mm_store_ss(xmm0, xmm1)
    ret

XMVectorSetX endp

    end
