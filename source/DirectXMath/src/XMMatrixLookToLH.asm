
include DirectXMath.inc

    .code

XMMatrixLookToLH proc XM_CALLCONV XMTHISPTR, EyePosition:FXMVECTOR, EyeDirection:FXMVECTOR, UpDirection:FXMVECTOR

  local R0:             XMVECTOR,
        R1:             XMVECTOR,
        R2:             XMVECTOR,
        D0:             XMVECTOR,
        D1:             XMVECTOR,
        D2:             XMVECTOR,
        NegEyePosition: XMVECTOR

if _XM_VECTORCALL_ eq 0
    _mm_store_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm2)
    _mm_store_ps(xmm2, xmm3)
endif

    _mm_store_ps(EyePosition,  xmm0)
    _mm_store_ps(UpDirection,  xmm2)

    _mm_store_ps(NegEyePosition, inl_XMVectorNegate(xmm0))

    _mm_store_ps(R2, XMVector3Normalize(xmm1))
    _mm_store_ps(xmm1, xmm0)
    XMVector3Normalize(XMVector3Cross(UpDirection, xmm1))
    _mm_store_ps(R0, xmm0)
    XMVector3Cross(R2, _mm_store_ps(xmm1, xmm0))
    _mm_store_ps(R1, xmm0)

    XMVector3Dot(R0, NegEyePosition)
    _mm_store_ps(D0, xmm0)
    XMVector3Dot(R1, NegEyePosition)
    _mm_store_ps(D1, xmm0)
    XMVector3Dot(R2, NegEyePosition)
    _mm_store_ps(D2, xmm0)

    XMVectorSelect(D0, R0, g_XMSelect1110.v)
    _mm_store_ps(D0, xmm0)
    XMVectorSelect(D1, R1, g_XMSelect1110.v)
    _mm_store_ps(D1, xmm0)
    XMVectorSelect(D2, R2, g_XMSelect1110.v)
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    _mm_store_ps(xmm0, D0)
    _mm_store_ps(xmm1, D1)

    inl_XMMatrixTranspose()

if _XM_VECTORCALL_ eq 0
    _mm_store_ps([rcx+0*16], xmm0)
    _mm_store_ps([rcx+1*16], xmm1)
    _mm_store_ps([rcx+2*16], xmm2)
    _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixLookToLH endp

    end
