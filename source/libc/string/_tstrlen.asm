; _TSTRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcslen proc string:LPTSTR

    ldr         rcx,string

if defined(__AVX__) and not defined(_UNICODE)

ifdef _WIN64
    mov         r8,rcx
endif
    mov         rax,rcx
    and         rax,-32
    and         ecx,32-1
    mov         edx,-1
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[rax]
    add         rax,32
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         .1
.0:
    vpcmpeqb    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    add         rax,32
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-32]
ifdef _WIN64
    sub         rax,r8
else
    sub         eax,string
endif

elseif defined(__SSE__) and not defined(_UNICODE)

ifdef _WIN64
    mov         r8,rcx
endif
    mov         rax,rcx
    and         rax,-16
    and         ecx,16-1
    or          edx,-1
    shl         edx,cl
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[rax]
    add         rax,16
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
    and         ecx,edx
    jnz         .1
.0:
    movaps      xmm1,[rax]
    pcmpeqb     xmm1,xmm0
    pmovmskb    ecx,xmm1
    add         rax,16
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-16]
ifdef _WIN64
    sub         rax,r8
else
    sub         eax,string
endif

else

    mov         rdx,rdi
    mov         rdi,rcx
    mov         rcx,-1
    xor         eax,eax
    repnz      .scasb
    mov         rax,rcx
    mov         rdi,rdx
    not         rax
    dec         rax

endif
    ret

_tcslen endp

    end
