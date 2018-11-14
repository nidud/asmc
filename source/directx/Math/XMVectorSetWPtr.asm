; XMVECTORSETWPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetWPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetWPtr(xmm0, [rdx])
    ret

XMVectorSetWPtr endp

    end
