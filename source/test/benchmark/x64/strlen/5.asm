
    option dotname

    .code

    mov         r10,rcx
    mov         rax,rcx
    and         rax,-32
    and         ecx,32-1
    mov         edx,-1
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[rax]
    add         rax,32
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         .1
.0:
    vpcmpeqb    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    add         rax,32
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-32]
    sub         rax,r10
    ret

    end
