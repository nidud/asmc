
    .code

    option dotname

    imul        edx,edx,0x01010101
    movd        xmm1,edx
    pshufd      xmm1,xmm1,0
    xorps       xmm0,xmm0

    mov         rax,rcx
    and         rax,-16
    movaps      xmm2,[rax]
    movaps      xmm3,xmm2
    add         rax,16

    and         ecx,0x0F
    mov         r8d,-1
    shl         r8d,cl

    pcmpeqb     xmm2,xmm0
    pcmpeqb     xmm3,xmm1
    pmovmskb    ecx,xmm2
    pmovmskb    edx,xmm3
    and         ecx,r8d
    and         edx,r8d
    jnz         .1

    align       8

.0:
    test        ecx,ecx
    jnz         .2
    movaps      xmm2,[rax]
    movaps      xmm3,xmm2
    pcmpeqb     xmm2,xmm0
    pcmpeqb     xmm3,xmm1
    pmovmskb    ecx,xmm2
    pmovmskb    edx,xmm3
    add         rax,16
    test        edx,edx
    jz          .0
.1:
    bsf         edx,edx
    lea         rax,[rax+rdx-16]
    test        ecx,ecx
    jz          .3
    bsf         ecx,ecx
    cmp         ecx,edx
    jae         .3
.2:
    xor         eax,eax
.3:
    ret

    end
