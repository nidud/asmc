; XMVECTORMODANGLES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorModAngles proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorModAngles(xmm0)
    ret

XMVectorModAngles endp

    end
