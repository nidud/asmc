; _TCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; size_t strlen(char *);
; size_t wcslen(wchar_t *);
;
include tchar.inc
include isa_availability.inc

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

ifdef _UNICODE
define xcmpeq pcmpeqw
ifdef __AVX__
define tcmpeq vpcmpeqw
else
define tcmpeq pcmpeqw
endif
else
define xcmpeq pcmpeqb
ifdef __AVX__
define tcmpeq vpcmpeqb
else
define tcmpeq pcmpeqb
endif
endif


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
    jnz     nocando
endif

ifdef __SSE__
    mov     rax,rcx         ; align back to avoid reading ahead
ifdef __AVX__
ifdef __TEST__
    mov     edx,0
    inc     edx
elseifdef __AVX512__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jnz     align_to_boundary
    jmp     nocando
endif

    align   main_loop size_t

align_to_boundary:

    and     al,-U
    and     cl,U-1
ifdef __AVX512__
    vxorps  zmm0,zmm0,zmm0
    or      rdx,-1          ; mask string part
ifdef _UNICODE
    shr     ecx,1           ; 32-bit mask
endif
    shl     rdx,cl          ; bits to keep
    kmovq   k1,rdx
    tcmpeq  k0{k1},zmm0,[rax]
    add     rax,64
    kmovq   rdx,k0
    test    rdx,rdx
elseifdef __AVX__
    or      edx,-1
    shl     edx,cl
    vxorps  ymm0,ymm0,ymm0
    tcmpeq  ymm1,ymm0,[rax]
    add     rax,32
    vpmovmskb ecx,ymm1
    and     edx,ecx
else
    or      edx,-1
    shl     edx,cl
    xorps   xmm0,xmm0
    xcmpeq  xmm0,[rax]
    add     rax,16
    pmovmskb ecx,xmm0
    xorps   xmm0,xmm0
    and     edx,ecx
endif
    jnz     toend

main_loop:
ifdef __AVX512__
    tcmpeq  k0,zmm0,[rax]
    kmovq   rdx,k0
elseifdef __AVX__
    tcmpeq  ymm1,ymm0,[rax]
    vpmovmskb edx,ymm1
else
    movaps  xmm1,[rax]
    xcmpeq  xmm1,xmm0
    pmovmskb edx,xmm1
endif
    add     rax,U
    test    rdx,rdx
    jz      main_loop

toend:
    bsf     rdx,rdx
if defined(_UNICODE) and defined(__AVX512__)
    lea     rax,[rax+rdx*2-U]
else
    lea     rax,[rax+rdx-U]
endif
    sub     rax,string
ifdef _UNICODE
    shr     rax,1
endif
    ret

endif ; __SSE__

if defined(_UNICODE) or defined(__AVX__) or not defined(__SSE__)

nocando:
ifndef _LIN64
    mov     rdx,rdi
    mov     rdi,rcx
endif
    or      rcx,-1
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
