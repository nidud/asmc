; XMVECTORGETINTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntY(xmm0)
    ret

XMVectorGetIntY endp

    end
