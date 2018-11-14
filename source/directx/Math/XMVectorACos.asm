; XMVECTORACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorACos proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorACos(xmm0)
    ret

XMVectorACos endp

    end
