; XMVECTORGETINTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntY proc XM_CALLCONV V:FXMVECTOR

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(1,1,1,1))
    _mm_cvtsi128_si32(xmm0)
    ret

XMVectorGetIntY endp

    end
