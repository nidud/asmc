
    option      dotname

    .code

    mov         rax,rcx
    mov         r10,rdx

    and         r10,-16
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[r10]
    pmovmskb    r9d,xmm0
    add         r10,16

    mov         cl,dl
    and         cl,16-1
    shr         r9d,cl

    test        r9d,r9d
    jz          .4

    bsf         ecx,r9d
    inc         ecx

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
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jz          .5

    bsf         ecx,ecx
    sub         r10,rdx
    lea         ecx,[r10+rcx+1]

    test        cl,11110000B
    jnz         .3
    test        cl,00001000B
    jnz         .2
    test        cl,00000100B
    jnz         .1
    jmp         .0

.5:
    movups      xmm2,[rdx]
    movups      [rax],xmm2

    add         r10,16
    mov         rcx,r10
    sub         rcx,rdx
    lea         rdx,[rax+rcx]
    movups      [rdx-16],xmm1
.6:
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jnz         .7

    movups      [rdx],xmm1
    add         rdx,16
    add         r10,16
    jmp         .6
.7:
    bsf         ecx,ecx
    movups      xmm0,[r10+rcx-15]
    movups      [rdx+rcx-15],xmm0
    ret

    end
