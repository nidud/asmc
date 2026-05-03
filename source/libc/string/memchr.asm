; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *memchr(void *dst, char c, size_t count);
;

include isa_availability.inc

.code

memchr::

ifdef _WIN64
    define  size <r8>
ifdef __UNIX__
    movzx   eax,sil
    mov     rcx,rdi
    mov     r8,rdx
else
    movzx   eax,dl
endif
else
    mov     ecx,[esp+4]
    movzx   eax,byte ptr [esp+8]
    define  size <dword ptr [esp+12]>
endif

ifdef __SSE__

    imul        eax,eax,0x01010101
    movd        xmm0,eax
    pshufd      xmm0,xmm0,0
    mov         rax,rcx

ifdef __AVX__

    cmp     size,64
    jb      memchr_sse
ifdef __TEST__
    mov     edx,0
    inc     edx
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz      memchr_sse

memchr_avx:

    and         al,-32
    and         cl,32-1
    or          edx,-1
    shl         edx,cl
    vperm2f128  ymm0,ymm0,ymm0,0
    vpcmpeqb    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         firstblock

    bsf         ecx,edx
    mov         rdx,size
    sub         rcx,32
    add         rdx,rcx
    jle         notfound

    align       size_t
loop_avx:
    add         rax,32
    vpcmpeqb    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    test        ecx,ecx
    jnz         found
    sub         rdx,32
    jg          loop_avx
    xor         eax,eax
    ret

    align       size_t
memchr_sse:

endif ; __AVX__

    and         al,-16
    and         cl,16-1
    or          edx,-1
    shl         edx,cl
    movaps      xmm1,xmm0
    pcmpeqb     xmm1,[rax]
    pmovmskb    ecx,xmm1
    and         ecx,edx
    jnz         firstblock

    bsf         ecx,edx
    mov         rdx,size
    sub         rcx,16
    add         rdx,rcx
    jle         notfound

    align       size_t
loop_sse:
    add         rax,16
    movaps      xmm1,xmm0
    pcmpeqb     xmm1,[rax]
    pmovmskb    ecx,xmm1
    test        ecx,ecx
    jnz         found
    sub         rdx,16
    jg          loop_sse
notfound:
    xor         eax,eax
    ret

    align       size_t
firstblock:
    bsf         rdx,rdx
    add         rdx,size

    align       size_t
found:
    bsf         ecx,ecx
    add         rax,rcx
    cmp         rdx,rcx
    mov         ecx,0
    cmovbe      rax,rcx
    ret

else ; __SSE__

    mov     edx,edi
    mov     edi,ecx
    mov     ecx,size
    repnz   scasb
    lea     eax,[edi-1]
    mov     edi,edx
    .ifnz
        mov rax,rcx
    .endif
    ret
endif
    end
