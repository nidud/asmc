
include stdio.inc
include directxmath.inc

.data
R XMVECTORF32 <>
V XMVECTORF32 {{{ 1.0, 2.0, 3.0, 4.0 }}}

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

main proc

  local pSin:float, pCos:float
  local Sin:double, Cos:double

    XMScalarSinCos(&pSin, &pCos, 0.5)
    _mm_store_sd(Sin, _mm_cvtss_sd(_mm_load_ss(xmm0, pSin)))
    _mm_store_sd(Cos, _mm_cvtss_sd(_mm_load_ss(xmm1, pCos)))
    printf("XMScalarSinCos:\t%f, %f\n", Sin, Cos)

    XMVectorLog2( V )
    movdqa R.v,xmm0
    print4("XMVectorLog2")
    XMVectorSin( V )
    movdqa R.v,xmm0
    print4("XMVectorSin")
    XMVectorCos( V )
    movdqa R.v,xmm0
    print4("XMVectorCos")
    XMVectorTan( V )
    movdqa R.v,xmm0
    print4("XMVectorTan")
    xor eax,eax
    ret

main endp

    end
