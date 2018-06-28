
include stdio.inc
include directxmath.inc

.code

main proc

  local x:XMUINT4, Value:UINT, result:double

    mov Value,1
    mov x.x,5
    mov x.y,5
    mov x.z,5
    mov x.w,5

    XMConvertVectorIntToFloat(x, Value)
    _mm_store_sd(result, _mm_cvtss_sd(xmm0))

    printf("result: %f\n", result)

    xor eax,eax
    ret

main endp

    end
