; XMVECTORGETINTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntW proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntW(xmm0)
    ret

XMVectorGetIntW endp

    end
