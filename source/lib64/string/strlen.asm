; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strlen::

ifdef _NOINTRINSICS

    push    rdi
    xor     eax,eax
    mov     rdi,rcx
    mov     rcx,-1
    repne   scasb
    not     rcx
    dec     rcx
    mov     rax,rcx
    pop     rdi
    ret

elseifdef __AVX512__

    mov             r8,rcx
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
    sub             rax,r8
    ret

elseif defined(__AVX__) or defined(__AVX2__)

    mov     r8,rcx
    mov     rax,rcx
    and     rax,-32
    and     ecx,32-1
    mov     edx,-1
    shl     edx,cl
    pxor    xmm0,xmm0
    vpcmpeqb ymm1,ymm0,[rax]
    add     rax,32
    vpmovmskb ecx,ymm1
    and     ecx,edx
    jnz     L2
L1:
    vpcmpeqb ymm1,ymm0,[rax]
    vpmovmskb ecx,ymm1
    add     rax,32
    test    ecx,ecx
    jz      L1
L2:
    bsf     ecx,ecx
    lea     rax,[rax+rcx-32]
    sub     rax,r8
    ret

else

    mov     r8,rcx
    mov     rax,rcx
    and     rax,-16
    and     ecx,16-1
    or      edx,-1
    shl     edx,cl
    xorps   xmm0,xmm0
    pcmpeqb xmm0,[rax]
    add     rax,16
    pmovmskb ecx,xmm0
    xorps   xmm0,xmm0
    and     ecx,edx
    jnz     L2
L1:
    movaps  xmm1,[rax]
    pcmpeqb xmm1,xmm0
    pmovmskb ecx,xmm1
    add     rax,16
    test    ecx,ecx
    jz      L1
L2:
    bsf     ecx,ecx
    lea     rax,[rax+rcx-16]
    sub     rax,r8
    ret

endif

    end
