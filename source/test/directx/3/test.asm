
include stdio.inc
include directxmath.inc

.code

main proc

  local x:XMFLOAT4, result:double

    mov x.x,0.5
    mov x.y,0.5
    mov x.z,0.5
    mov x.w,0.5

    XMVectorSin(x)
    printf("\nXMVectorSin(0.5): %f\n", _mm_store_sd(result, _mm_cvtss_sd(xmm0)))
    xor eax,eax
    ret

main endp

    end
