; _TCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcslen proc string:LPTSTR

    ldr         rcx,string

ifdef __AVX__

ifdef _UNICODE
    test        cl,1            ; Unicode strings needs to be aligned..
    jnz         .3
endif
ifdef _WIN64
    mov         r8,rcx
endif
    mov         rax,rcx         ; align back to avoid reading ahead
    and         rax,-32
    and         ecx,32-1
    mov         edx,-1          ; mask string part
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
ifdef _UNICODE
    vpcmpeqw    ymm1,ymm0,[rax]
else
    vpcmpeqb    ymm1,ymm0,[rax]
endif
    add         rax,32
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         .1
.0:
ifdef _UNICODE
    vpcmpeqw    ymm1,ymm0,[rax]
else
    vpcmpeqb    ymm1,ymm0,[rax]
endif
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
ifdef _UNICODE
    shr         eax,1
.2:
endif
    ret

elseifdef __SSE__

ifdef _UNICODE
    test        cl,1
    jnz         .3
endif

ifdef _WIN64
    mov         r8,rcx
endif
    mov         rax,rcx
    and         rax,-16
    and         ecx,16-1
    or          edx,-1
    shl         edx,cl
    xorps       xmm0,xmm0
ifdef _UNICODE
    pcmpeqw     xmm0,[rax]
else
    pcmpeqb     xmm0,[rax]
endif
    add         rax,16
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
    and         ecx,edx
    jnz         .1
.0:
    movaps      xmm1,[rax]
ifdef _UNICODE
    pcmpeqw     xmm1,xmm0
else
    pcmpeqb     xmm1,xmm0
endif
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
ifdef _UNICODE
    shr         eax,1
.2:
endif
    ret

else

    mov         rdx,rdi
    mov         rdi,rcx
    mov         rcx,-1
    xor         eax,eax
    repnz       _tscasb
    mov         rax,rcx
    mov         rdi,rdx
    not         rax
    dec         rax
    ret

endif

if defined(_UNICODE) and ( defined(__AVX__) or defined(__SSE__) )
.3:
    mov         rdx,rdi
    mov         rdi,rcx
    mov         rcx,-1
    xor         eax,eax
    repnz       scasw
    mov         rax,rcx
    mov         rdi,rdx
    not         rax
    dec         rax
    jmp         .2
endif

_tcslen endp

    end
