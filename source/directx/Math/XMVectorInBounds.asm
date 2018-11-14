; XMVECTORINBOUNDS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorInBounds proc XM_CALLCONV V:FXMVECTOR, Bounds:FXMVECTOR

    inl_XMVectorInBounds(xmm0, xmm1)
    ret

XMVectorInBounds endp

    end
