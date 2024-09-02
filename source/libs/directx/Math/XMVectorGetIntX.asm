; XMVECTORGETINTX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntX proc XM_CALLCONV V:FXMVECTOR

    ldr xmm0,V

    _mm_cvtsi128_si32(xmm0)
    ret

XMVectorGetIntX endp

    end
