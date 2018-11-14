; XMVECTORSETX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetX proc XM_CALLCONV V:FXMVECTOR, x:float

    inl_XMVectorSetX(xmm0, xmm1)
    ret

XMVectorSetX endp

    end
