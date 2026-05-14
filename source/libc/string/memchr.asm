; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *memchr(void *dst, char c, size_t count);
;

include libc.inc

ifdef __AVX__
if defined(__AVX512BW__) and defined(_WIN64)
define __AVX512__
define U 64
else
define U 32
endif
else
define U 16
endif

.code

memchr proc

ifdef __SSE__

ifndef _WIN64
    mov     eax,[esp+4]
    movzx   edx,byte ptr [esp+8]
    mov     ecx,[esp+12]
elseifdef __UNIX__
    mov     rax,rdi
    mov     rcx,rdx
    movzx   edx,sil
else
    mov     rax,rcx
    movzx   edx,dl
    mov     rcx,r8
endif

ifdef __AVX512__
    vpbroadcastb zmm0,edx
else
    imul    edx,edx,0x01010101
    movd    xmm0,edx
ifdef __AVX__
    vbroadcastss ymm0,xmm0
else
    pshufd  xmm0,xmm0,0
endif
endif

    test    rcx,rcx
    jz      not_found

    lea     rdx,[rcx+rax]
    test    al,U-1
    jz      main_loop

ifdef _WIN64
    mov     r8,rdx
else
    push    edx
endif
    mov     cl,al
    and     al,-U
    and     ecx,U-1

ifdef __AVX512__
    vpcmpeqb k1,zmm0,[rax]
    kmovq   rdx,k1
elseifdef __AVX__
    vpcmpeqb ymm1,ymm0,[rax]
    vpmovmskb edx,ymm1
else
    movaps  xmm1,xmm0
    pcmpeqb xmm1,[rax]
    pmovmskb edx,xmm1
endif
    shr     rdx,cl      ; shift out low bits..
    shl     rdx,cl
    mov     rcx,rdx
ifdef _WIN64
    mov     rdx,r8
else
    pop     edx
endif
    add     rax,U
    test    rcx,rcx
    jnz     char_found

    align   size_t

main_loop:

    cmp     rax,rdx
    jae     not_found

ifdef __AVX512__
    vpcmpeqb k1,zmm0,[rax]
    kmovq   rcx,k1
elseifdef __AVX__
    vpcmpeqb ymm1,ymm0,[rax]
    vpmovmskb ecx,ymm1
else
    movaps  xmm1,xmm0
    pcmpeqb xmm1,[rax]
    pmovmskb ecx,xmm1
endif
    add     rax,U
    test    rcx,rcx
    jz      main_loop

char_found:
    bsf     rcx,rcx
    lea     rax,[rax+rcx-U]
    xor     ecx,ecx
    cmp     rax,rdx
    cmovae  rax,rcx
ifdef __AVX__
    vzeroupper
endif
    ret

not_found:
    xor     eax,eax
ifdef __AVX__
    vzeroupper
endif
ifdef USE_BYTE
    ret
endif

else ; __SSE__

ifndef _WIN64
    mov     edx,[esp+4]
    movzx   eax,byte ptr [esp+8]
    mov     ecx,[esp+12]
    xchg    edx,edi
elseifdef __UNIX__
    movzx   eax,sil
    mov     rcx,rdx
else
    movzx   eax,dl
    mov     rdx,rdi
    mov     rdi,rcx
    mov     rcx,r8
endif
    test    rdi,rdi
    repnz   scasb
    lea     rax,[rdi-1]
ifndef _LIN64
    mov     rdi,rdx
endif
ifdef __SSE__
    cmovnz  rax,rcx
else
    jz      toend
    mov     rax,rcx
toend:
endif
endif
    ret
    endp

    end
