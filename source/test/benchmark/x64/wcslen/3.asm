
    option dotname

    .code

    test        cl,1
    jnz         .2

    mov         r10,rcx
    mov         rax,rcx
    and         rax,-32
    and         ecx,32-1
    mov         edx,-1
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqw    ymm1,ymm0,[rax]
    add         rax,32
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         .1
.0:
    vpcmpeqw    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    add         rax,32
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-32]
    sub         rax,r10
    shr         eax,1
    ret
.2:
    mov         rdx,rdi
    mov         rdi,rcx
    mov         rcx,-1
    xor         eax,eax
    repnz       scasw
    mov         rax,rcx
    mov         rdi,rdx
    not         rax
    dec         rax
    ret

    end
