; XMMATRIXTRANSLATION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixTranslation proc XM_CALLCONV OffsetX:float, OffsetY:float, OffsetZ:float

    XMVectorSet(xmm0, xmm1, xmm2, 1.0)
    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    ret

XMMatrixTranslation endp

    end
