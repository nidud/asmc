; XMVECTORGETZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetZ proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetZ(xmm0)
    ret

XMVectorGetZ endp

    end
