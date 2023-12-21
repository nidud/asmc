; STRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

if defined(__AVX__) and defined(_WIN64)

strchr::
ifdef __UNIX__
    mov         rcx,rdi
    movzx       edx,sil
else
    movzx       edx,dl
endif
    imul        edx,edx,0x01010101
    movd        xmm1,edx
    pshufd      xmm1,xmm1,0
    vperm2f128  ymm1,ymm1,ymm1,0
    vxorps      ymm0,ymm0,ymm0
    mov         rax,rcx
    and         al,0xE0
    vpcmpeqb    ymm2,ymm0,[rax]
    vpcmpeqb    ymm3,ymm1,[rax]
    add         rax,32
    and         cl,0x1F
    or          r8d,-1
    shl         r8d,cl
    vpmovmskb   ecx,ymm2
    vpmovmskb   edx,ymm3
    and         ecx,r8d
    and         edx,r8d
    jnz         .1
.0:
    test        ecx,ecx
    jnz         .2
    vpcmpeqb    ymm2,ymm0,[rax]
    vpcmpeqb    ymm3,ymm1,[rax]
    vpmovmskb   ecx,ymm2
    vpmovmskb   edx,ymm3
    add         rax,32
    test        edx,edx
    jz          .0
.1:
    bsf         edx,edx
    lea         rax,[rax+rdx-32]
    test        ecx,ecx
    jz          .3
    bsf         ecx,ecx
    cmp         ecx,edx
    ja          .3
.2:
    xor         eax,eax
.3:
    ret

else

strchr proc string:string_t, chr:int_t

    ldr     rax,string
    ldr     ecx,chr
    movzx   ecx,cl
.3:
    cmp     cl,[rax]
    je      .0
    cmp     ch,[rax]
    je      .4
    cmp     cl,[rax+1]
    je      .1
    cmp     ch,[rax+1]
    je      .4
    cmp     cl,[rax+2]
    je      .2
    cmp     ch,[rax+2]
    je      .4
    add     rax,3
    jmp     .3
.4:
    xor     eax,eax
    jmp     .0
.2:
    inc     rax
.1:
    inc     rax
.0:
    ret

strchr endp
endif
    end
