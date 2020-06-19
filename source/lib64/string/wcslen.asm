; WCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

wcslen::

if defined(__AVX__) or defined(__AVX2__)

    test    ecx,1
    jnz     L3
    mov     r8,rcx
    mov     rax,rcx
    and     rax,-32
    and     ecx,32-1
    mov     edx,-1
    shl     edx,cl
    pxor    xmm0,xmm0
    vpcmpeqw ymm1,ymm0,[rax]
    add     rax,32
    vpmovmskb ecx,ymm1
    and     ecx,edx
    jnz     L2
L1:
    vpcmpeqw ymm1,ymm0,[rax]
    vpmovmskb ecx,ymm1
    add     rax,32

else

    bt      ecx,0
    jc      L3
    mov     r8,rcx
    mov     rax,rcx
    and     rax,-16
    and     ecx,16-1
    or      edx,-1
    shl     edx,cl
    pxor    xmm0,xmm0
    pcmpeqw xmm0,[rax]
    add     rax,16
    pmovmskb ecx,xmm0
    pxor    xmm0,xmm0
    and     ecx,edx
    jnz     L2
L1:
    movaps  xmm1,[rax]
    pcmpeqw xmm1,xmm0
    pmovmskb ecx,xmm1
    add     rax,16

endif

    test    ecx,ecx
    jz      L1
L2:
    bsf     ecx,ecx
    lea     rax,[rax+rcx-16]
    sub     rax,r8
    shr     rax,1
    ret
L3:
    xor     eax,eax
    mov     rdx,rdi
    mov     rdi,rcx
    mov     rcx,-1
    repne   scasw
    mov     rdi,rdx
    not     rcx
    dec     rcx
    mov     rax,rcx
    ret

    end
