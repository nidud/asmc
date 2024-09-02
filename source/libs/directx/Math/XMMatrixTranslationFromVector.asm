; XMMATRIXTRANSLATIONFROMVECTOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixTranslationFromVector proc XM_CALLCONV Offs:FXMVECTOR

    XMVectorSelect(g_XMIdentityR3.v, xmm0, g_XMSelect1110.v)
    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    ret

XMMatrixTranslationFromVector endp

    end
