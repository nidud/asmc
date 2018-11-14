; XMVECTORCOSEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorCosEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorCosEst(xmm0)
    ret

XMVectorCosEst endp

    end
