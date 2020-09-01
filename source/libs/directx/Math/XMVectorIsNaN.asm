; XMVECTORISNAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorIsNaN proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorIsNaN(xmm0)
    ret

XMVectorIsNaN endp

    end
