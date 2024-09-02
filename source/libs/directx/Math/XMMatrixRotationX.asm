; XMMATRIXROTATIONX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixRotationX proc XM_CALLCONV Scale:float

    XMScalarSinCos(NULL, NULL, xmm0)
    ;;
    ;; x = 0,y = cos,z = sin, w = 0
    ;;
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(3,0,0,3))
    ;;
    ;; x = 0,y = sin,z = cos, w = 0
    ;;
    XM_PERMUTE_PS(_mm_store_ps(xmm2, xmm1), _MM_SHUFFLE(3,1,2,0))
    ;;
    ;; x = 0,y = -sin,z = cos, w = 0
    ;;
    _mm_mul_ps(xmm2, g_XMNegateY)
    _mm_store_ps(xmm0, g_XMIdentityR0)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    ret

XMMatrixRotationX endp

    end
