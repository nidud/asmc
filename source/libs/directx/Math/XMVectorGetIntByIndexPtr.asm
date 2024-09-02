; XMVECTORGETINTBYINDEXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntByIndexPtr proc XM_CALLCONV f:ptr uint32_t, V:FXMVECTOR, i:size_t

    movaps xmmword ptr f,xmm1
    mov    eax,dword ptr f[r8*4]
    mov    [rcx],eax
    ret

XMVectorGetIntByIndexPtr endp

    end
