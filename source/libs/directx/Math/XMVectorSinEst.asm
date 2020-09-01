; XMVECTORSINEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSinEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSinEst(xmm0)
    ret

XMVectorSinEst endp

    end
