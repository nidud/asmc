; XMVECTORREPLICATEINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReplicateInt proc XM_CALLCONV Value:uint32_t

    ldr ecx,Value

    movd xmm0,ecx
    XM_PERMUTE_PS()
    ret

XMVectorReplicateInt endp

    end
