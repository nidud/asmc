; XMVECTORGETY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetY(xmm0)
    ret

XMVectorGetY endp

    end
