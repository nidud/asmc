
include DirectXMath.inc

    .data

    TMask            XMVECTORU32 { { { 0x1, 0x1, 0x1, 0x1 } } }
    TanConstants     XMVECTORF32 { { { 1.570796371, 6.077100628e-11, 0.000244140625, 0.63661977228 } } }
    TanCoefficients0 XMVECTORF32 { { { 1.0, -4.667168334e-1, 2.566383229e-2, -3.118153191e-4 } } }
    TanCoefficients1 XMVECTORF32 { { { 4.981943399e-7, -1.333835001e-1, 3.424887824e-3, -1.786170734e-5 } } }

    .code

    option win64:rsp nosave noauto

XMVectorTan proc XM_CALLCONV V:FXMVECTOR

if _XM_VECTORCALL_ eq 0
    _mm_storeu_ps(xmm0, [rcx])
endif
    _mm_store_ps(V, xmm0)
    _mm_store_ps(V[16], xmm6)
    _mm_store_ps(V[32], xmm7)
    _mm_store_ps(xmm7, xmm0)

    _mm_store_ps(xmm1, TanConstants.v)
    _mm_store_ps(xmm4, xmm1)
    _mm_store_ps(xmm5, xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3, 3, 3, 3))
    inl_XMVectorRound(_mm_mul_ps(xmm0, xmm1))
    XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(0, 0, 0, 0))
    _mm_sub_ps(xmm7, _mm_mul_ps(xmm4, xmm0))
    _mm_sub_ps(_mm_setzero_ps(xmm1), xmm0)
    _mm_store_ps(xmm6, xmm0)
    _mm_max_ps(xmm6, xmm1)
    _mm_cvttps_epi32(xmm6)
    XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_sub_ps(xmm7, _mm_mul_ps(xmm5, xmm0))
    _mm_mul_ps(_mm_store_ps(xmm0, xmm7), xmm0)
    _mm_store_ps(xmm2, TanCoefficients1.v)
    _mm_store_ps(xmm3, xmm2)
    _mm_store_ps(xmm4, xmm2)
    _mm_store_ps(xmm5, xmm2)
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(3, 3, 3, 3))
    XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(2, 2, 2, 2))
    XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(1, 1, 1, 1))
    XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(0, 0, 0, 0))
    _mm_store_ps(xmm1, xmm0)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm2), xmm3)
    _mm_store_ps(xmm2, TanCoefficients0.v)
    _mm_store_ps(xmm3, xmm2)
    XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(3, 3, 3, 3))
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), xmm3)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), xmm4)
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), xmm2)
    _mm_mul_ps(xmm0, xmm1)
    _mm_store_ps(xmm2, TanCoefficients0.v)
    _mm_store_ps(xmm3, xmm2)
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), xmm2)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm7), xmm7)
    _mm_store_ps(xmm2, TanConstants.v)
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_store_ps(xmm4, xmm7)
    _mm_cmple_ps(xmm4, xmm2)
    _mm_mul_ps(xmm2, g_XMNegativeOne)
    _mm_cmple_ps(xmm2, xmm7)
    _mm_and_ps(xmm4, xmm2)
    XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0, 0, 0, 0))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), xmm3)
    _mm_store_ps(xmm2, xmm4)
    _mm_and_ps(xmm7, xmm2)
    _mm_andnot_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, xmm7)
    _mm_store_ps(xmm3, g_XMOne.v)
    _mm_and_ps(xmm3, xmm4)
    _mm_andnot_ps(xmm4, xmm5)
    _mm_or_ps(xmm4, xmm3)
    _mm_sub_ps(_mm_setzero_ps(xmm3), xmm2)
    _mm_div_ps(xmm2, xmm4)
    _mm_div_ps(xmm4, xmm3)
    _mm_and_ps(xmm6, TMask.v)
    _mm_cmpeq_epi32(xmm6, _mm_setzero_ps(xmm1))
    _mm_cmpeq_ps(xmm1, V)
    _mm_and_ps(xmm2, xmm6)
    _mm_andnot_ps(xmm6, xmm4)
    _mm_or_ps(xmm6, xmm2)
    _mm_and_ps(_mm_setzero_ps(), xmm1)
    _mm_andnot_ps(xmm1, xmm6)
    _mm_or_ps(xmm0, xmm1)

    _mm_store_ps(xmm6, V[16])
    _mm_store_ps(xmm7, V[32])
    ret

XMVectorTan endp

    end
