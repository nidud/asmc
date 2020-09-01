; XMVECTORGETX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetX proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetX(xmm0)
    ret

XMVectorGetX endp

    end
