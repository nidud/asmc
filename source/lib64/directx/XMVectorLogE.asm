
include DirectXMath.inc

    .code

XMVectorLogE proc XM_CALLCONV V:FXMVECTOR

  local x6:XMVECTOR, x7:XMVECTOR
  local exponentSub:XMVECTOR
if _XM_VECTORCALL_ eq 0
    _mm_storeu_ps(xmm0, [rcx])
endif
    _mm_store_ps(x6, xmm6)
    _mm_store_ps(x7, xmm7)
    _mm_store_ps(xmm6, xmm0)

    ;; Compute exponent and significand for subnormals.

    _mm_and_si128(_mm_store_ps(xmm7, g_XMQNaNTest), xmm0)
    XMVECTOR::GetLeadingBit(xmm7)

    _mm_sub_epi32(_mm_store_ps(xmm1, g_XMNumTrailing), xmm0)
    _mm_sub_epi32(_mm_store_ps(xmm0, g_XMSubnormalExponent), xmm1)
    _mm_store_ps(exponentSub, xmm0)
    XMVECTOR::multi_sll_epi32(xmm7, xmm1)
    _mm_and_si128(xmm0, g_XMQNaNTest)

    _mm_and_si128(_mm_store_ps(xmm1, xmm6), g_XMInfinity)
    _mm_store_ps(xmm5, xmm1)
    _mm_cmpeq_epi32(xmm1, g_XMZero)
    _mm_and_si128(_mm_store_ps(xmm2, xmm1), exponentSub)
    _mm_sub_epi32(_mm_srli_epi32(xmm5, 23), g_XMExponentBias)
    _mm_andnot_si128(_mm_store_ps(xmm3, xmm1), xmm5)

    _mm_or_si128(xmm2, xmm3)
    _mm_and_si128(xmm0, xmm1)
    _mm_andnot_si128(xmm1, xmm7)
    _mm_or_si128(xmm0, xmm1)
    _mm_or_si128(xmm0, g_XMOne)
    _mm_sub_ps(xmm0, g_XMOne)
    _mm_store_ps(xmm1, xmm0)

    _mm_mul_ps(xmm0, g_XMLogEst7)
    _mm_add_ps(xmm0, g_XMLogEst6)

    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst5)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst4)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst3)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst2)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst1)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), g_XMLogEst0)
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_cvtepi32_ps(xmm2))

    _mm_mul_ps(xmm0, g_XMInvLgE)

    ;;  if (x is NaN) -> QNaN
    ;;  else if (V is positive)
    ;;      if (V is infinite) -> +inf
    ;;      else -> log2(V)
    ;;  else
    ;;      if (V is zero) -> -inf
    ;;      else -> -QNaN

    _mm_store_ps(xmm1, xmm6)
    _mm_and_si128(xmm1, g_XMAbsMask)
    _mm_cmpeq_epi32(xmm1, g_XMInfinity)

    _mm_store_ps(xmm2, xmm6)
    _mm_store_ps(xmm3, xmm6)

    _mm_cmpgt_epi32(xmm2, g_XMZero)
    _mm_cmpgt_epi32(xmm3, g_XMInfinity)
    _mm_andnot_si128(xmm3, xmm2)

    _mm_store_ps(xmm2, xmm6)
    _mm_and_si128(xmm2, g_XMAbsMask)
    _mm_cmpeq_epi32(xmm2, g_XMZero)

    _mm_store_ps(xmm4, xmm6)
    _mm_and_si128(xmm4, g_XMQNaNTest)
    _mm_and_si128(xmm6, g_XMInfinity)
    _mm_cmpeq_epi32(xmm4, g_XMZero)
    _mm_cmpeq_epi32(xmm6, g_XMInfinity)
    _mm_andnot_si128(xmm4, xmm6)

    _mm_store_ps(xmm5, xmm1)
    _mm_and_si128(xmm5, g_XMInfinity)
    _mm_andnot_si128(xmm1, xmm0)
    _mm_or_si128(xmm5, xmm1)

    _mm_store_ps(xmm0, xmm2)
    _mm_and_si128(xmm0, g_XMNegInfinity);
    _mm_andnot_si128(xmm2, g_XMNegQNaN);
    _mm_or_si128(xmm0, xmm2)

    _mm_store_ps(xmm2, xmm3)
    _mm_and_si128(xmm2, xmm5)
    _mm_andnot_si128(xmm3, xmm0)
    _mm_or_si128(xmm2, xmm3)

    _mm_store_ps(xmm0, xmm4)
    _mm_and_si128(xmm0, g_XMQNaN)
    _mm_andnot_si128(xmm4, xmm2)
    _mm_or_si128(xmm0, xmm4)

    _mm_store_ps(xmm6, x6)
    _mm_store_ps(xmm7, x7)
    ret

XMVectorLogE endp

    end
