; XMVECTORSETINTXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntXPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr uint32_t

    inl_XMVectorSetIntXPtr(xmm0, [rdx])
    ret

XMVectorSetIntXPtr endp

    end
