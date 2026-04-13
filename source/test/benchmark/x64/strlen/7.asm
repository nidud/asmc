
    .code

    pxor        xmm0,xmm0
    mov         rax,rcx
    mov         rdx,rcx
    and         al,-16
    pcmpistri   xmm0,[rax],8
    jnz         L1
    add         rax,rcx
    cmp         rax,rdx
    jae         L2
    sub         rax,rcx
    align       16
L1:
    add         rax,16
    pcmpistri   xmm0,[rax],8
    jnz         L1
    add         rax,rcx
L2:
    sub         rax,rdx
    ret

    end
