; XMVECTORREPLICATEINTPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReplicateIntPtr proc XM_CALLCONV pValue:ptr uint32_t

    ldr rcx,pValue

    _mm_load_ps1([rcx])
    ret

XMVectorReplicateIntPtr endp

    end
