; XMVECTORSPLATY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatY proc XM_CALLCONV V:FXMVECTOR

    ldr xmm0,V

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(1, 1, 1, 1))
    ret

XMVectorSplatY endp

    end
