; XMVECTORLESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorLess proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorLess(xmm0, xmm1)
    ret

XMVectorLess endp

    end
