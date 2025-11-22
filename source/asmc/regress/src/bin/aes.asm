;
; AES Encryption / Decryption -- updated v2.37.38
;
ifdef __ASMC__
ifndef __ASMC64__
    .x64
    .model flat
endif
endif
    .code

    aesdeclast      xmm1,xmm2
    aesdeclast      xmm1,[rax]
    aesdeclast      xmm1,[rdi]

    aesenclast      xmm1,xmm2
    aesenclast      xmm1,[rax]
    aesenclast      xmm1,[rdi]

    aesdec          xmm1,xmm2
    aesdec          xmm1,[rax]
    aesenc          xmm1,xmm2
    aesenc          xmm1,[rax]

    aesimc          xmm1,xmm2
    aesimc          xmm1,[rax]

    aeskeygenassist xmm1,xmm2,1

    aesenc128kl     xmm1,[rax]
    aesenc128kl     xmm2,[rdi]

    aesdec128kl     xmm1,[rax]
    aesdec128kl     xmm2,[rdi]

    aesdecwide128kl [rax]
    aesdecwide128kl [rdi]

    aesdecwide256kl [rax]
    aesdecwide256kl [rdi]

    aesencwide128kl [rax]
    aesencwide128kl [rdi]

    aesencwide256kl [rax]
    aesencwide256kl [rdi]

    vaesdeclast     xmm1,xmm2,xmm3
    vaesdeclast     xmm1,xmm2,[rax]
    vaesdeclast     ymm1,ymm2,ymm3
    vaesdeclast     ymm1,ymm2,[rax]
    vaesdeclast     zmm1,zmm2,zmm3
    vaesdeclast     zmm1,zmm2,[rax]

    vaesenclast     xmm1,xmm2,xmm3
    vaesenclast     xmm1,xmm2,[rax]
    vaesenclast     ymm1,ymm2,ymm3
    vaesenclast     ymm1,ymm2,[rax]
    vaesenclast     zmm1,zmm2,zmm3
    vaesenclast     zmm1,zmm2,[rax]

    vaesimc         xmm1,xmm2
    vaesimc         xmm1,[rax]

    vaeskeygenassist xmm1,xmm2,1

    end
