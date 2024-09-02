; XMVECTORREPLICATEPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReplicatePtr proc XM_CALLCONV pValue:ptr float

    ldr rcx,pValue

    _mm_load_ps1([rcx])
    ret

XMVectorReplicatePtr endp

    end
