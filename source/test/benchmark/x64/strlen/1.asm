    .code

    mov         r10,rcx
    mov         rax,rcx
    and         al,0xF0
    and         cl,0x0F
    mov         edx,-1
    shl         edx,cl
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[rax]
    add         rax,16
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
    and         ecx,edx
    jnz         L2
L1:
    movaps      xmm1,[rax]
    pcmpeqb     xmm1,xmm0
    pmovmskb    ecx,xmm1
    add         rax,16
    test        ecx,ecx
    jz          L1
L2:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-16]
    sub         rax,r10
    ret

    end
