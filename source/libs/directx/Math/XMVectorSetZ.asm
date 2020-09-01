; XMVECTORSETZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetZ proc XM_CALLCONV V:FXMVECTOR, x:float

    inl_XMVectorSetW(xmm0, xmm1)
    ret

XMVectorSetZ endp

    end
