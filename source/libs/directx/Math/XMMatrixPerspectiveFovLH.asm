; XMMATRIXPERSPECTIVEFOVLH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixPerspectiveFovLH proc XM_CALLCONV uses xmm6 FovAngleY:float, AspectRatio:float, NearZ:float, FarZ:float

    _mm_store_ss(xmm5, xmm1)
    _mm_store_ss(xmm4, xmm2)
    _mm_store_ss(xmm6, xmm3)

    XMScalarSinCos(NULL, NULL, _mm_mul_ss(xmm0, 0.5))

    _mm_move_ss(xmm3, xmm0)
    _mm_div_ss(xmm3, xmm1)
    _mm_store_ps(xmm0, xmm6)
    _mm_sub_ss(xmm0, xmm4)
    _mm_div_ss(xmm6, xmm0)
    _mm_store_ps(xmm0, xmm3)
    _mm_div_ss(xmm0, xmm5)
    _mm_store_ps(xmm1, xmm6)
    _mm_xor_ps(xmm1, _mm_get_epi32(0x80000000, 0, 0, 0))
    _mm_mul_ss(xmm1, xmm4)
    _mm_unpacklo_ps(xmm6, xmm1)
    _mm_setzero_ps(xmm1)
    _mm_store_ps(xmm2, xmm1)
    _mm_unpacklo_ps(xmm0, xmm3)
    _mm_movelh_ps(xmm0, xmm6)
    _mm_move_ss(xmm2, xmm0)
    _mm_store_ps(xmm4, xmm2)
    _mm_store_ps(xmm2, g_XMMaskY)
    _mm_and_ps(xmm2, xmm0)
    _mm_shuffle_ps(xmm0, g_XMIdentityR3, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(3,0,0,0))
    _mm_store_ps(xmm5, xmm1)
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(2,1,0,0))
    _mm_store_ps(xmm3, xmm1)
    _mm_store_ps(xmm0, xmm4)
    _mm_store_ps(xmm1, xmm2)
    _mm_store_ps(xmm2, xmm5)
    ret

XMMatrixPerspectiveFovLH endp

    end
