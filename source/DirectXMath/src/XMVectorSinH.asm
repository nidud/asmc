
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSinH proc XM_CALLCONV V:FXMVECTOR
if _XM_VECTORCALL_ eq 0
    _mm_storeu_ps(xmm0, [rcx])
endif
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, _mm_get_epi32(1.442695040888963, 1.442695040888963, 1.442695040888963, 1.442695040888963))
    _mm_store_ps(xmm3, g_XMNegativeOne)
    _mm_mul_ps(xmm0, xmm2)
    _mm_add_ps(xmm0, xmm3)
    _mm_mul_ps(xmm1, xmm2)
    _mm_sub_ps(xmm3, xmm1)
    _mm_store_ps(V, xmm1)
    XMVectorExp(xmm0)
    _mm_store_ps(xmm1, V)
    _mm_store_ps(V, xmm0)
    XMVectorExp(xmm1)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, V)
    _mm_sub_ps(xmm0, xmm1)
    ret

XMVectorSinH endp

    end
