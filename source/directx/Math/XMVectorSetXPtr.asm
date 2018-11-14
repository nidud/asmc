; XMVECTORSETXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetXPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetXPtr(xmm0, [rdx])
    ret

XMVectorSetXPtr endp

    end
