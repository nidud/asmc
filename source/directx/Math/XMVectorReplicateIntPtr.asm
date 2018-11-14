; XMVECTORREPLICATEINTPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicateIntPtr proc XM_CALLCONV pValue:ptr uint32_t

    inl_XMVectorReplicateIntPtr(rcx)
    ret

XMVectorReplicateIntPtr endp

    end
