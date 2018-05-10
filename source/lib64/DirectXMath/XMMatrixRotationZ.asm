include DirectXMath.inc

    .code

XMMatrixRotationZ proc Angle:float

    local SinAngle:float
    local CosAngle:float

    XMScalarSinCos(&SinAngle, &CosAngle, xmm3);Angle)

    _mm_load_ss(xmm0, SinAngle)
    _mm_load_ss(xmm1, CosAngle)
    _mm_shuffle_ps(xmm0, xmm1, _MM_SHUFFLE(3,0,3,0))
    _mm_store_ps(xmm2, xmm0)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    _mm_mul_ps(xmm0, g_XMNegateZ)
    _mm_store_ps(xmm1, g_XMIdentityR1)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    ret

XMMatrixRotationZ endp

    end

