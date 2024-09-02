; XMMATRIXROTATIONZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixRotationZ proc XM_CALLCONV Scale:float

    XMScalarSinCos(NULL, NULL, xmm0)

    _mm_unpacklo_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,2,0,1))
    _mm_mul_ps(xmm1, g_XMNegateX)
    _mm_store_ps(xmm2, g_XMIdentityR2)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    ret

XMMatrixRotationZ endp

    end
