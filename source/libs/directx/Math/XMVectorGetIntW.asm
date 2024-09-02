; XMVECTORGETINTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntW proc XM_CALLCONV V:FXMVECTOR

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,3,3,3))
    _mm_cvtsi128_si32(xmm0)
    ret

XMVectorGetIntW endp

    end
