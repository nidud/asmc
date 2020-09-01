; XMVECTOR3NORMALIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVector3Normalize proc XM_CALLCONV V:FXMVECTOR

    inl_XMVector3Normalize(xmm0)
    ret

XMVector3Normalize endp

    end
