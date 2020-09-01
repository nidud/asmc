; XMVECTORGREATER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGreater proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorGreater(xmm0, xmm1)
    ret

XMVectorGreater endp

    end
