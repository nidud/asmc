; XMVECTORGETX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetX proc XM_CALLCONV V:FXMVECTOR

    _mm_cvtss_f32(xmm0)
    ret

XMVectorGetX endp

    end
