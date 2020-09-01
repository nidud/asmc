; XMVECTORCOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorCos proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorCos(xmm0)
    ret

XMVectorCos endp

    end
