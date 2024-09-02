; XMMATRIXROTATIONY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixRotationY proc XM_CALLCONV Scale:float

    XMScalarSinCos(NULL, NULL, xmm0)

    _mm_store_ps(xmm2, _mm_shuffle_ps(xmm0, xmm1, _MM_SHUFFLE(3,0,3,0)))
    _mm_mul_ps(XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2)), g_XMNegateZ)
    _mm_store_ps(xmm1, g_XMIdentityR1)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    ret

XMMatrixRotationY endp

    end
