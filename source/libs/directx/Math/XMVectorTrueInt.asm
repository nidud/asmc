; XMVECTORTRUEINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorTrueInt proc XM_CALLCONV

    mov eax,-1
    movd xmm0,eax
    XM_PERMUTE_PS()
    ret

XMVectorTrueInt endp

    end
