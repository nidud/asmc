
include DirectXMath.inc

    .code

XMVectorTanEst proc XM_CALLCONV V:FXMVECTOR

  local OneOverPi:      XMVECTOR,
        V1:             XMVECTOR,
        T0:             XMVECTOR,
        T1:             XMVECTOR,
        T2:             XMVECTOR,
        V2T2:           XMVECTOR,
        V2:             XMVECTOR,
        V1T0:           XMVECTOR,
        V1T1:           XMVECTOR,
        D:              XMVECTOR,
        N:              XMVECTOR

    _mm_store_ps(V, xmm0)
    _mm_store_ps(OneOverPi, XMVectorSplatW(g_XMTanEstCoefficients.v))

    XMVectorRound(XMVectorMultiply(V, OneOverPi))
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(V1, <XMVectorNegativeMultiplySubtract(g_XMPi.v, xmm1, V)>)

    _mm_store_ps(T0, XMVectorSplatX(g_XMTanEstCoefficients.v))
    _mm_store_ps(T1, XMVectorSplatY(g_XMTanEstCoefficients.v))
    _mm_store_ps(T2, XMVectorSplatZ(g_XMTanEstCoefficients.v))

    _mm_store_ps(V2T2, <XMVectorNegativeMultiplySubtract(V1, V1, T2)>)
    _mm_store_ps(V2, <XMVectorMultiply(V1, V1)>)
    _mm_store_ps(V1T0, <XMVectorMultiply(V1, T0)>)
    _mm_store_ps(V1T1, <XMVectorMultiply(V1, T1)>)

    _mm_store_ps(D, XMVectorReciprocalEst(V2T2))
    _mm_store_ps(N, <XMVectorMultiplyAdd(V2, V1T1, V1T0)>)

    XMVectorMultiply(N, D)
    ret

XMVectorTanEst endp

    end
