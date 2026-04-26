; _TCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include tchar.inc
include isa_availability.inc

.code

_tcslen::

ifndef _WIN64
    mov     ecx,[esp+4]
    define  string <[esp+4]>
elseifdef __UNIX__
    mov     rcx,rdi
    define  string <rdi>
else
    define  string <r8>
    mov     r8,rcx
endif

if defined(_UNICODE) and defined(__SSE__)
    test    cl,1            ; Unicode strings needs to be aligned..
    jnz     unicode_unaligned
endif

ifdef __SSE__
    mov     rax,rcx         ; align back to avoid reading ahead
ifdef __AVX__
ifdef __TEST__
    mov     edx,0
    inc     edx
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz      strlen_sse
    and     al,-32
    and     rcx,32-1
    mov     edx,-1          ; mask string part
    shl     edx,cl
    vxorps  ymm0,ymm0,ymm0
ifdef _UNICODE
    vpcmpeqw ymm1,ymm0,[rax]
else
    vpcmpeqb ymm1,ymm0,[rax]
endif
    add     rax,32
    vpmovmskb ecx,ymm1
    and     ecx,edx
    jnz     end_avx

    align   size_t
loop_avx:
ifdef _UNICODE
    vpcmpeqw ymm1,ymm0,[rax]
else
    vpcmpeqb ymm1,ymm0,[rax]
endif
    vpmovmskb ecx,ymm1
    add     rax,32
    test    ecx,ecx
    jz      loop_avx
end_avx:
    bsf     ecx,ecx
    lea     rax,[rax+rcx-32]
    sub     rax,string
ifdef _UNICODE
    shr     eax,1
endif
    ret
strlen_sse:
endif

    and     rax,-16
    and     ecx,16-1
    or      edx,-1
    shl     edx,cl
    xorps   xmm0,xmm0
ifdef _UNICODE
    pcmpeqw xmm0,[rax]
else
    pcmpeqb xmm0,[rax]
endif
    add     rax,16
    pmovmskb ecx,xmm0
    xorps   xmm0,xmm0
    and     ecx,edx
    jnz     end_sse

    align   8
loop_sse:
    movaps  xmm1,[rax]
ifdef _UNICODE
    pcmpeqw xmm1,xmm0
else
    pcmpeqb xmm1,xmm0
endif
    pmovmskb ecx,xmm1
    add     rax,16
    test    ecx,ecx
    jz      loop_sse
end_sse:
    bsf     ecx,ecx
    lea     rax,[rax+rcx-16]
    sub     rax,string
ifdef _UNICODE
    shr     eax,1
endif
    ret

endif ; __SSE__

if defined(_UNICODE) or not defined(__SSE__)
unicode_unaligned:
ifndef _LIN64
    mov     rdx,rdi
    mov     rdi,rcx
endif
    mov     rcx,-1
    xor     eax,eax
    repnz   _tscasb
    mov     rax,rcx
ifndef _LIN64
    mov     rdi,rdx
endif
    not     rax
    dec     rax
    ret
endif
    end
