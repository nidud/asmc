
    .code

    mov             r10,rcx
    xor             eax,eax
    vpbroadcastq    zmm0,rax
    dec             rax
    and             ecx,64-1
    shl             rax,cl
    kmovq           k2,rax
    mov             rax,r8
    and             rax,-64
    vpcmpeqb        k1{k2},zmm0,[rax]
    jmp             L2
L1:
    vpcmpeqb        k1,zmm0,[rax]
L2:
    kmovq           rcx,k1
    add             rax,64
    test            rcx,rcx
    jz              L1
    bsf             rcx,rcx
    lea             rax,[rax+rcx-64]
    sub             rax,r10
    ret

    end
