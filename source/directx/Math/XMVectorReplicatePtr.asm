; XMVECTORREPLICATEPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicatePtr proc XM_CALLCONV pValue:ptr float

    inl_XMVectorReplicatePtr(rcx)
    ret

XMVectorReplicatePtr endp

    end
