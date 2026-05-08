; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *memchr(void *dst, char c, size_t count);
;

include isa_availability.inc

if defined(__AVX__) or not defined(__SSE__)
define USE_BYTE
endif

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

ifdef _WIN64
    test    r8,r8
else
    cmp     size,0
endif
    jz      not_found

ifdef __AVX__
ifdef __TEST__
    mov     edx,0
    inc     edx
elseifdef __AVX512__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz      use_byte
endif

ifdef __AVX512__
    vpbroadcastb zmm0,al
else
    imul    eax,eax,0x01010101
    movd    xmm0,eax
    pshufd  xmm0,xmm0,0
endif
    mov     rax,rcx
    and     al,-U
    and     ecx,U-1
ifdef __AVX512__
    vpcmpeqb k1,zmm0,[rax]
    kmovq   rdx,k1
elseifdef __AVX__
    vperm2f128 ymm0,ymm0,ymm0,0
    vpcmpeqb ymm1,ymm0,[rax]
    vpmovmskb edx,ymm1
else
    movaps  xmm1,xmm0
    pcmpeqb xmm1,[rax]
    pmovmskb edx,xmm1
endif
    shr     rdx,cl      ; shift out low bits..
    shl     rdx,cl
    xchg    rcx,rdx
    add     rdx,rax     ; end of buffer
    add     rdx,size
    test    rcx,rcx
    jnz     found
    align   size_t
main_loop:
    add     rax,U
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
    test    rcx,rcx
    jz      main_loop
found:
    bsf     rcx,rcx
    add     rax,rcx
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

endif ; __SSE__

ifdef USE_BYTE
use_byte:
    mov     rdx,rdi
    mov     rdi,rcx
    mov     rcx,size
    test    rdi,rdi
    repnz   scasb
    lea     rax,[rdi-1]
    mov     rdi,rdx
ifdef __SSE__
    cmovnz  rax,rcx
else
    jz      toend
    mov     rax,rcx
endif
toend:
endif
    ret
    endp
    end
