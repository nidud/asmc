; XMVECTORSPLATZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatZ proc XM_CALLCONV V:FXMVECTOR

    ldr xmm0,V

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(2, 2, 2, 2))
    ret

XMVectorSplatZ endp

    end
