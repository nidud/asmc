; XMVECTORSPLATX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatX proc XM_CALLCONV V:FXMVECTOR

    ldr xmm0,V

    XM_PERMUTE_PS()
    ret

XMVectorSplatX endp

    end
