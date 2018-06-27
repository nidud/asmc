
include stdio.inc
include directxmath.inc

.code

main proc

  local pSin:float, pCos:float, Value:float
  local Sin:double, Cos:double

    mov Value,0.5

    XMScalarSinCos(&pSin, &pCos, Value)

    _mm_store_sd(Sin, _mm_cvtss_sd(_mm_load_ss(xmm0, pSin)))
    _mm_store_sd(Cos, _mm_cvtss_sd(_mm_load_ss(xmm1, pCos)))

    printf("Sin: %f\nCos: %f\n", Sin, Cos)

    xor eax,eax
    ret

main endp

    end
