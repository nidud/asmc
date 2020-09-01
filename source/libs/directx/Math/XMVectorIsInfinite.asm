; XMVECTORISINFINITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorIsInfinite proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorIsInfinite(xmm0)
    ret

XMVectorIsInfinite endp

    end
