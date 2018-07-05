
include stdio.inc
include directxmath.inc

.data
R  XMVECTORF32 <>
R2 XMVECTORF32 <>
V  XMVECTORF32 {{{ 0.5, 1.0, 3.0, 4.0 }}}
V2 XMVECTORF32 {{{ 5.0, 6.0, 7.0, 8.0 }}}

.code

print4 proc string:LPSTR

  local f0:double, f1:double, f2:double, f3:double

    _mm_store_sd(f0, _mm_cvtss_sd(_mm_load_ss(xmm0, R.f[0])))
    _mm_store_sd(f1, _mm_cvtss_sd(_mm_load_ss(xmm0, R.f[4])))
    _mm_store_sd(f2, _mm_cvtss_sd(_mm_load_ss(xmm0, R.f[8])))
    _mm_store_sd(f3, _mm_cvtss_sd(_mm_load_ss(xmm0, R.f[12])))
    printf("%s:\t%f, %f, %f, %f\n", string, f0, f1, f2, f3)
    ret

print4 endp

run macro p
    p( V )
    movdqa R.v,xmm0
    print4("&p&")
    exitm<>
    endm

run2 macro p
    p( V, V2 )
    movdqa R.v,xmm0
    print4("&p&")
    exitm<>
    endm

main proc

  local pSin:float, pCos:float
  local Sin:double, Cos:double

    XMScalarSinCos(&pSin, &pCos, 0.5)
    _mm_store_sd(Sin, _mm_cvtss_sd(_mm_load_ss(xmm0, pSin)))
    _mm_store_sd(Cos, _mm_cvtss_sd(_mm_load_ss(xmm1, pCos)))
    printf("XMScalarSinCos:\t\t%f, %f\n", Sin, Cos)

    XMVectorSinCosEst(&R, &R2, V)
    movdqa R.v,xmm0
    movdqa R2.v,xmm1
    print4("XMVectorSinCosEst")
    movdqa xmm0,R2.v
    movdqa R.v,xmm0
    print4("XMVectorSinCosEst")
    XMVectorModAngles( V )
    movdqa R.v,xmm0
    print4("XMVectorModAngles")

    run(XMVectorLog2)
    run(XMVectorSin)
    run(XMVectorSinH)
    run(XMVectorCos)
    run(XMVectorCosH)
    run(XMVectorExp)
    run(XMVectorTan)
    run(XMVectorTanH)
    run(XMVectorASin)
    run(XMVectorACos)
    run(XMVectorATan)
    run2(XMVectorATan2)
    run(XMVectorSinEst)
    run(XMVectorCosEst)
    run(XMVectorTanEst)
    run(XMVector3Normalize)
    run2(XMVector3Cross)
    run2(XMVector3Dot)
    xor eax,eax
    ret

main endp

    end
