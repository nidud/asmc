; XMVECTORGETINTXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntXPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    inl_XMVectorGetIntXPtr([rcx], xmm1)
    ret

XMVectorGetIntXPtr endp

    end
