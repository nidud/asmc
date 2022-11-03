
    option dotname

    .code

    push    rsi
    push    rdi

    mov     rax,rcx
    mov     rsi,rdx
    and     rsi,-4

    and     edx,3
    lea     ecx,[rdx*8]

    mov     edi,-1
    shl     edi,cl
    not     edi
    or      edi,[rsi]

    lea     ecx,[rdi-0x01010101]
    not     edi
    and     ecx,edi
    and     ecx,0x80808080
    jnz     .3

    mov     ecx,[rsi+rdx]
    mov     [rax],ecx

    sub     edx,4
    neg     edx
    add     rdx,rax
    jmp     .1

    align   8

.0:
    mov     ecx,[rsi]
    mov     [rdx],ecx
    add     rdx,4
.1:
    add     rsi,4
    mov     ecx,[rsi]
    lea     edi,[rcx-0x01010101]
    not     ecx
    and     edi,ecx
    and     edi,0x80808080
    jz      .0
    bsf     edi,edi
    shr     rdi,3
    mov     ecx,[rsi+rdi-3]
    mov     [rdx+rdi-3],ecx
.2:
    pop     rdi
    pop     rsi
    ret
.3:
    add     rdx,rsi
    mov     cl,[rdx]
    mov     [rax],cl
    test    cl,cl
    jz      .2
    mov     cl,[rdx+1]
    mov     [rax+1],cl
    test    cl,cl
    jz      .2
    mov     cl,[rdx+2]
    mov     [rax+2],cl
    test    cl,cl
    jz      .2
    mov     cl,[rdx+3]
    mov     [rax+3],cl
    jmp     .2

    end
