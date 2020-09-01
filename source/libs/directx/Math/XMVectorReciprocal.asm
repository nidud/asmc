; XMVECTORRECIPROCAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocal proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocal(xmm0)
    ret

XMVectorReciprocal endp

    end
