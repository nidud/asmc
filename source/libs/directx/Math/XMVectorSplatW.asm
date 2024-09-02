; XMVECTORSPLATW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatW proc XM_CALLCONV V:FXMVECTOR

    ldr xmm0,V

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3, 3, 3, 3))
    ret

XMVectorSplatW endp

    end
