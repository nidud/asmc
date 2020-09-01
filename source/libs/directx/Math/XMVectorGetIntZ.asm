; XMVECTORGETINTZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntZ proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntZ(xmm0)
    ret

XMVectorGetIntZ endp

    end
