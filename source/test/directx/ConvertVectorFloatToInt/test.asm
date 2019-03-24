
include stdio.inc
include directxmath.inc

.code

main proc

  local x:XMFLOAT4, value:UINT, result:UINT

    mov value,2
    mov x.x,5.0
    ;mov x.y,5.0
    ;mov x.z,5.0
    ;mov x.w,5.0

    XMConvertVectorFloatToInt(x, value)

    movd eax,xmm0
    printf("result: %d\n", eax)

    xor eax,eax
    ret

main endp

    end
