; XMVECTORSPLATY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSplatY()
    ret

XMVectorSplatY endp

    end
