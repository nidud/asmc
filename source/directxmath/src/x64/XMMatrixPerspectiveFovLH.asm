include DirectXMath.inc

    .code

XMMatrixPerspectiveFovLH proc FovAngleY:float, AspectRatio:float, NearZ:float, FarZ:float

  local SinFov:float, CosFov:float
  local fRange:float, Height:float

    mov fRange,0.5
    _mm_mul_ss(xmm0, fRange)
    _mm_store_ss(fRange, xmm0)

    XMScalarSinCos(&SinFov, &CosFov, fRange)

    _mm_move_ss(xmm4, SinFov)
    _mm_div_ss(xmm4, CosFov)
    _mm_move_ss(xmm3, FarZ)
    _mm_store_ps(xmm0, xmm3)
    _mm_move_ss(xmm2, NearZ)
    _mm_sub_ss(xmm0, xmm2)
    _mm_move_ss(xmm1, AspectRatio)
    _mm_div_ss(xmm3, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_div_ss(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm3)
    _mm_xor_ps(xmm1, _mm_get_epi32(0x80000000, 0, 0, 0))
    _mm_unpacklo_ps(xmm0, xmm4)
    _mm_mul_ss(xmm2, xmm1)
    _mm_setzero_ps(xmm1)
    _mm_unpacklo_ps(xmm3, xmm2)
    _mm_store_ps(xmm2, xmm1)
    _mm_movelh_ps(xmm0, xmm3)
    _mm_move_ss(xmm2, xmm0)
    _mm_store_ps(xmm4, xmm2)
    _mm_store_ps(xmm1, g_XMMaskY)
    _mm_and_ps(xmm1, xmm0)
    _mm_shuffle_ps(xmm0, g_XMIdentityR3, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(3,0,0,0))
    _mm_shuffle_ps(xmm3, xmm0, _MM_SHUFFLE(2,1,0,0))
    _mm_store_ps(xmm0, xmm4)
    ret

XMMatrixPerspectiveFovLH endp

    end

