; _TCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcschr proc string:tstring_t, chr:int_t

    ldr     rax,string
    ldr     edx,chr

if defined(__AVX__) and defined(_WIN64) and not defined(_UNICODE)

    movzx       edx,dl
    imul        edx,edx,0x01010101
    movd        xmm1,edx
    pshufd      xmm1,xmm1,0
    vperm2f128  ymm1,ymm1,ymm1,0
    vxorps      ymm0,ymm0,ymm0
    mov         ecx,eax
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

else

.3:
    cmp     _tdl,[rax]
    je      .0
    cmp     tchar_t ptr [rax],0
    je      .4
    cmp     _tdl,[rax+tchar_t]
    je      .1
    cmp     tchar_t ptr [rax+tchar_t],0
    je      .4
    cmp     _tdl,[rax+2*tchar_t]
    je      .2
    cmp     tchar_t ptr [rax+2*tchar_t],0
    je      .4
    add     rax,3*tchar_t
    jmp     .3
.4:
    xor     eax,eax
    jmp     .0
.2:
    add     rax,tchar_t
.1:
    add     rax,tchar_t
.0:

endif

    ret

_tcschr endp

    end
