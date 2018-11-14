; XMVECTORRECIPROCALEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocalEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocalEst(xmm0)
    ret

XMVectorReciprocalEst endp

    end
