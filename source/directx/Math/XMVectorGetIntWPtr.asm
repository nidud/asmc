; XMVECTORGETINTWPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntWPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    inl_XMVectorGetIntWPtr(rcx, xmm1)
    ret

XMVectorGetIntWPtr endp

    end
