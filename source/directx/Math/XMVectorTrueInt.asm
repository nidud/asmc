; XMVECTORTRUEINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorTrueInt proc XM_CALLCONV

    mov eax,-1
    movd xmm0,eax
    XM_PERMUTE_PS()
    ret

XMVectorTrueInt endp

    end
