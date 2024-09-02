; XMVECTORREPLICATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReplicate proc XM_CALLCONV Value:float

    ldr xmm0,Value

    XM_PERMUTE_PS()
    ret

XMVectorReplicate endp

    end
