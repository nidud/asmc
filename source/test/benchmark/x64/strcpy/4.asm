
    option      dotname

    .code

    mov         rax,rcx
    mov         r10,rdx

    and         r10,-32
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[r10]
    vpmovmskb   r9d,ymm1
    add         r10,32

    mov         cl,dl
    and         cl,32-1
    shr         r9d,cl

    test        r9d,r9d
    jz          .5

    bsf         ecx,r9d
    inc         ecx

    test        cl,11110000B
    jnz         .3
    test        cl,00001000B
    jnz         .2
    test        cl,00000100B
    jnz         .1
    test        cl,00000010B
    jnz         .0

    mov         cl,[rdx]
    mov         [rax],cl
    ret
.0:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [rax+rcx-2],dx
    mov         [rax],r8w
    ret
.1:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [rax+rcx-4],edx
    mov         [rax],r8d
    ret
.2:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [rax],r8
    mov         [rax+rcx-8],rdx
    ret
.3:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [rax],xmm0
    movups      [rax+rcx-16],xmm1
    ret
.4:
    vmovups     ymm0,[rdx]
    vmovups     ymm1,[rdx+rcx-32]
    vmovups     [rax],ymm0
    vmovups     [rax+rcx-32],ymm1
    ret

.5:

    vmovaps     ymm1,[r10]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jz          .6

    bsf         ecx,ecx
    sub         r10,rdx
    lea         ecx,[r10+rcx+1]
    cmp         ecx,32
    ja          .4
    test        cl,00110000B
    jnz         .3
    test        cl,00001000B
    jnz         .2
    test        cl,00000100B
    jnz         .1
    jmp         .0

    align       8

.6:

    vmovups     ymm2,[rdx]
    vmovups     [rax],ymm2

    add         r10,32
    mov         rcx,r10
    sub         rcx,rdx
    lea         rdx,[rax+rcx]
    vmovups     [rdx-32],ymm1
.7:
    vmovaps     ymm1,[r10]
    vpcmpeqb    ymm2,ymm0,ymm1
    vpmovmskb   ecx,ymm2
    test        ecx,ecx
    jnz         .8

    vmovups     [rdx],ymm1
    add         rdx,32
    add         r10,32
    jmp         .7
.8:
    bsf         ecx,ecx
    vmovups     ymm1,[r10+rcx-31]
    vmovups     [rdx+rcx-31],ymm1
    ret

    end
