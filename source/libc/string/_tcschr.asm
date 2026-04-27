; _TCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include tchar.inc
include isa_availability.inc

    .code

    option dotname

_tcschr::

ifndef _WIN64
    mov     eax,[esp+4]
    movzx   edx,tchar_t ptr [esp+8]
elseifdef __UNIX__
    mov     rax,rdi
ifdef _UNICODE
    movzx   edx,si
else
    movzx   edx,sil
endif
else
    mov     rax,rcx
    movzx   edx,_tdl
endif

ifdef __SSE__

ifdef __AVX__
define CHUNK 32
else
define CHUNK 16
endif

ifdef _UNICODE
ifdef __AVX__
define tcmpeq vpcmpeqw
else
define tcmpeq pcmpeqw
endif
define mval 0x00010001
else
ifdef __AVX__
define tcmpeq vpcmpeqb
else
define tcmpeq pcmpeqb
endif
define mval 0x01010101
endif
ifdef _UNICODE
    test        al,1
    jnz         .byte_scan
endif
ifdef __AVX__
ifdef __TEST__
    mov         ecx,0
    inc         ecx
else
    test        __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz          .byte_scan
endif
    imul        edx,edx,mval
    movd        xmm1,edx
    pshufd      xmm1,xmm1,0
ifdef __AVX__
    vperm2f128  ymm1,ymm1,ymm1,0
    vxorps      ymm0,ymm0,ymm0
else
    xorps       xmm0,xmm0
endif
    mov         ecx,eax
    and         al,-CHUNK
ifdef __AVX__
    tcmpeq      ymm2,ymm0,[rax]
    tcmpeq      ymm3,ymm1,[rax]
else
    movaps      xmm2,[rax]
    movaps      xmm3,[rax]
    tcmpeq      xmm2,xmm0
    tcmpeq      xmm3,xmm1
endif
    add         rax,CHUNK
    and         cl,CHUNK-1
ifdef _WIN64
    or          r8d,-1
    shl         r8d,cl
else
    push        ebx
    or          ebx,-1
    shl         ebx,cl
endif
ifdef __AVX__
    vpmovmskb   ecx,ymm2
    vpmovmskb   edx,ymm3
else
    pmovmskb    ecx,xmm2
    pmovmskb    edx,xmm3
endif
ifdef _WIN64
    and         ecx,r8d
    and         edx,r8d
else
    and         ecx,ebx
    and         edx,ebx
    pop         ebx
endif
    jnz         .vchar
.vloop:
    test        ecx,ecx
    jnz         .vnull
ifdef __AVX__
    tcmpeq      ymm2,ymm0,[rax]
    tcmpeq      ymm3,ymm1,[rax]
    vpmovmskb   ecx,ymm2
    vpmovmskb   edx,ymm3
else
    movaps      xmm2,[rax]
    movaps      xmm3,[rax]
    tcmpeq      xmm2,xmm0
    tcmpeq      xmm3,xmm1
    pmovmskb    ecx,xmm2
    pmovmskb    edx,xmm3
endif
    add         rax,CHUNK
    test        edx,edx
    jz          .vloop
.vchar:
    bsf         edx,edx
    lea         rax,[rax+rdx-CHUNK]
    test        ecx,ecx
    jz          .vend
    bsf         ecx,ecx
    cmp         ecx,edx
    ja          .vend
.vnull:
    xor         eax,eax
.vend:
ifdef __AVX__
    vzeroupper
endif
    ret

endif

if defined(_UNICODE) or defined(__AVX__) or not defined(__SSE__)

.byte_scan:
ifdef _UNICODE
    movzx   ecx,word ptr [rax]
    cmp     ecx,edx
    je      .toend
    test    ecx,ecx
    je      .null
    movzx   ecx,word ptr [rax+2]
    cmp     ecx,edx
    je      .one
    test    ecx,ecx
    je      .null
    movzx   ecx,word ptr [rax+4]
    cmp     ecx,edx
    je      .two
    add     rax,6
    test    ecx,ecx
else
    cmp     dl,[rax]
    je      .toend
    cmp     dh,[rax]
    je      .null
    cmp     dl,[rax+1]
    je      .one
    cmp     dh,[rax+1]
    je      .null
    cmp     dl,[rax+2]
    je      .two
    add     rax,3
    cmp     dh,[rax-1]
endif
    jnz     .byte_scan
.null:
    xor     eax,eax
    ret
.two:
    add     rax,tchar_t
.one:
    add     rax,tchar_t
.toend:
    ret

endif

    end
