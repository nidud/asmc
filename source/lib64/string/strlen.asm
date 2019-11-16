; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strlen::

if defined(__AVX__) or defined(__AVX2__)

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
