; XMVECTORSETBYINDEXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetByIndexPtr proc XM_CALLCONV V:FXMVECTOR, f:ptr float, i:size_t

    mov    eax,[rdx]
    mov    dword ptr V[r8*4],eax
    movaps xmm0,V
    ret

XMVectorSetByIndexPtr endp

    end
