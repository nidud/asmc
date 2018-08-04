;
; Note: test case
;
include DirectXMath.inc

    .data

    ATan2Constants XMVECTORF32 { { { XM_PI, XM_PIDIV2, XM_PIDIV4, XM_PI * 3.0 / 4.0 } } }

    .code

XMVectorATan2 proc XM_CALLCONV Y:FXMVECTOR, X:FXMVECTOR

    ;; Return the inverse tangent of Y / X in the range of -Pi to Pi with the following exceptions:

    ;;       Y == 0 and X is Negative     -> Pi with the sign of Y
    ;;       y == 0 and x is positive     -> 0 with the sign of y
    ;;       Y != 0 and X == 0            -> Pi / 2 with the sign of Y
    ;;       Y != 0 and X is Negative     -> atan(y/x) + (PI with the sign of Y)
    ;;       X == -Infinity and Finite Y      -> Pi with the sign of Y
    ;;       X == +Infinity and Finite Y      -> 0 with the sign of Y
    ;;       Y == Infinity and X is Finite    -> Pi / 2 with the sign of Y
    ;;       Y == Infinity and X == -Infinity -> 3Pi / 4 with the sign of Y
    ;;       Y == Infinity and X == +Infinity -> Pi / 4 with the sign of Y

  local Zero:           XMVECTOR,
        ATanResultValid:XMVECTOR,
        Pi:             XMVECTOR,
        PiOverTwo:      XMVECTOR,
        PiOverFour:     XMVECTOR,
        ThreePiOverFour:XMVECTOR,
        YEqualsZero:    XMVECTOR,
        XEqualsZero:    XMVECTOR,
        XIsPositive:    XMVECTOR,
        YEqualsInfinity:XMVECTOR,
        XEqualsInfinity:XMVECTOR,
        YSign:          XMVECTOR,
        R0:             XMVECTOR,
        R1:             XMVECTOR,
        R2:             XMVECTOR,
        R3:             XMVECTOR,
        R4:             XMVECTOR,
        R5:             XMVECTOR,
        V:              XMVECTOR,
        Result:         XMVECTOR

    _mm_store_ps(X, xmm1)
    _mm_store_ps(Y, xmm0)

    _mm_store_ps(Zero, XMVectorZero())
    _mm_store_ps(ATanResultValid, XMVectorTrueInt())

    _mm_store_ps(Pi, XMVectorSplatX(ATan2Constants))
    _mm_store_ps(PiOverTwo, XMVectorSplatY(ATan2Constants))
    _mm_store_ps(PiOverFour, XMVectorSplatZ(ATan2Constants))
    _mm_store_ps(ThreePiOverFour, XMVectorSplatW(ATan2Constants))

    movaps YEqualsZero, XMVectorEqual(Y, Zero)
    movaps XEqualsZero, XMVectorEqual(X, Zero)
    movaps XIsPositive, XMVectorAndInt(X, g_XMNegativeZero.v)
    movaps XIsPositive, XMVectorEqualInt(XIsPositive, Zero)
    movaps YEqualsInfinity, XMVectorIsInfinite(Y)
    movaps XEqualsInfinity, XMVectorIsInfinite(X)

    movaps YSign, XMVectorAndInt(Y, g_XMNegativeZero.v)
    movaps Pi, XMVectorOrInt(Pi, YSign)
    movaps PiOverTwo, XMVectorOrInt(PiOverTwo, YSign)
    movaps PiOverFour, XMVectorOrInt(PiOverFour, YSign)
    movaps ThreePiOverFour, XMVectorOrInt(ThreePiOverFour, YSign)

    movaps R1, XMVectorSelect(Pi, YSign, XIsPositive)
    movaps R2, XMVectorSelect(ATanResultValid, PiOverTwo, XEqualsZero)
    movaps R3, XMVectorSelect(R2, R1, YEqualsZero)
    movaps R4, XMVectorSelect(ThreePiOverFour, PiOverFour, XIsPositive)
    movaps R5, XMVectorSelect(PiOverTwo, R4, XEqualsInfinity)
    movaps Result, XMVectorSelect(R3, R5, YEqualsInfinity)
    movaps ATanResultValid, XMVectorEqualInt(Result, ATanResultValid)

    _mm_store_ps(V, _mm_div_ps(Y, X))

    _mm_store_ps(R0, XMVectorATan(V))

    XMVectorSelect(Pi, g_XMNegativeZero, XIsPositive)
    _mm_store_ps(R1, xmm0)
    _mm_store_ps(R2, _mm_add_ps(R0, R1))
    XMVectorSelect(Result, R2, ATanResultValid)
    ret

XMVectorATan2 endp

    end
