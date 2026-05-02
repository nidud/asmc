
    .code

    mov     rdx,rcx
    mov     rax,-1
    and     ecx,64-1
    shl     rax,cl
    kmovq   k2,rax
    mov     rax,rdx
    and     rax,-64
    vxorps  zmm0,zmm0,zmm0
    vpcmpeqb k1{k2},zmm0,[rax]
L1:
    add     rax,64
    kmovq   rcx,k1
    test    rcx,rcx
    jnz     L2
    vpcmpeqb k1,zmm0,[rax]
    jmp     L1
L2:
    bsf rcx,rcx
    lea rax,[rax+rcx-64]
    sub rax,rdx
    ret
    end
