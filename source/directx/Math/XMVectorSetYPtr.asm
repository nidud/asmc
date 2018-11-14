; XMVECTORSETYPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetYPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetYPtr(xmm0, [rdx])
    ret

XMVectorSetYPtr endp

    end
