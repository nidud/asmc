
    option dotname

    .code

    test        cl,1
    jnz         .2

    mov         r10,rcx
    mov         rax,rcx
    and         al,0xF0
    and         cl,0x0F
    mov         edx,-1
    shl         edx,cl
    xorps       xmm0,xmm0
    pcmpeqw     xmm0,[rax]
    add         rax,16
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
    and         ecx,edx
    jnz         .1
.0:
    movaps      xmm1,[rax]
    pcmpeqw     xmm1,xmm0
    pmovmskb    ecx,xmm1
    add         rax,16
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-16]
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
