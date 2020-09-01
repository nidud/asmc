; XMVECTORSELECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSelect proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, Control:FXMVECTOR

    inl_XMVectorSelect(xmm0, xmm1, xmm2)
    ret

XMVectorSelect endp

    end
