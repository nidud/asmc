; XMVECTORNEGATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNegate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorNegate(xmm0)
    ret

XMVectorNegate endp

    end
