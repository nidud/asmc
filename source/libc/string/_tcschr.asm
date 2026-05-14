; _TCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strchr(char *, int);
; wchar_t *wcschr(wchar_t *, int);
;
include tchar.inc

if defined(_UNICODE) or not defined(__SSE__)
define USE_BYTECOPY
endif
if defined(__AVX512BW__) and defined(_WIN64)
define __AVX512__
endif

ifdef __AVX__
ifdef _UNICODE
define tcmpeq vpcmpeqw
else
define tcmpeq vpcmpeqb
endif
ifdef __AVX512__
define U 64
else
define U 32
endif
elseifdef __SSE__
ifdef _UNICODE
define tcmpeq pcmpeqw
else
define tcmpeq pcmpeqb
endif
define U 16
endif

.code

_tcschr proc

ifndef _WIN64
    mov     ecx,[esp+4]
    movzx   edx,tchar_t ptr [esp+8]
elseifdef __UNIX__
    mov     rcx,rdi
ifdef _UNICODE
    movzx   edx,si
else
    movzx   edx,sil
endif
else
ifdef USE_BYTECOPY
    movzx   edx,_tdl
endif
endif
    mov     rax,rcx

ifdef __SSE__

ifdef _UNICODE
    test    al,1
    jnz     byte_scan
endif

ifdef __AVX512__
ifdef _UNICODE
    vpbroadcastw zmm1,edx
else
    vpbroadcastb zmm1,edx
endif
    vxorps  zmm0,zmm0,zmm0
else
ifndef _UNICODE
    mov     dh,dl
endif
    movd    xmm1,edx
    pshuflw xmm1,xmm1,0;11110000b
ifdef __AVX__
    vbroadcastss ymm1,xmm1
    vxorps  ymm0,ymm0,ymm0
else
    pshufd  xmm1,xmm1,0
    xorps   xmm0,xmm0
endif
endif

    test    al,U-1
    jz      source_aligned

    and     al,-U
    and     ecx,U-1         ; shift count
ifdef __AVX512__
ifdef _UNICODE
    shr     ecx,1           ; 32-bit mask
endif
    or      rdx,-1
    shl     rdx,cl
    kmovq   k2,rdx
    tcmpeq  k0{k2},zmm0,[rax]
    tcmpeq  k1{k2},zmm1,[rax]
    kmovq   rcx,k0
    kmovq   rdx,k1
else
ifndef _WIN64
    push    ebx
    define  r8d <ebx>
endif
    or      r8d,-1
    shl     r8d,cl
ifdef __AVX__
    tcmpeq  ymm2,ymm0,[rax]
    tcmpeq  ymm3,ymm1,[rax]
    vpmovmskb ecx,ymm2
    vpmovmskb edx,ymm3
else
    movaps  xmm2,xmm0
    movaps  xmm3,xmm1
    tcmpeq  xmm2,[rax]
    tcmpeq  xmm3,[rax]
    pmovmskb ecx,xmm2
    pmovmskb edx,xmm3
endif
    and     ecx,r8d
    and     edx,r8d
ifndef _WIN64
    pop     ebx
endif
endif
    jmp     source_unaligned

main_loop:

    test    rcx,rcx
    jnz     zero_found

source_aligned:

ifdef __AVX512__
    tcmpeq  k0,zmm0,[rax]
    tcmpeq  k1,zmm1,[rax]
    kmovq   rcx,k0
    kmovq   rdx,k1
elseifdef __AVX__
    tcmpeq  ymm0,ymm0,[rax]
    tcmpeq  ymm2,ymm1,[rax]
    vpmovmskb ecx,ymm0
    vpmovmskb edx,ymm2
else
    movaps  xmm2,[rax]
    tcmpeq  xmm0,[rax]
    tcmpeq  xmm2,xmm1
    pmovmskb ecx,xmm0
    pmovmskb edx,xmm2
endif

source_unaligned:

    add     rax,U
ifdef __AVX512__
    test    rdx,rdx
else
    test    edx,edx
endif
    jz      main_loop

char_found:
ifdef __AVX512__
    bsf     rdx,rdx
    lea     rax,[rax+rdx*TCHAR-U]
else
    bsf     edx,edx
    lea     rax,[rax+rdx-U]
endif
ifdef __AVX512__
    test    rcx,rcx
else
    test    ecx,ecx
endif
    jz      end_loop
ifdef __AVX512__
    bsf     rcx,rcx
else
    bsf     ecx,ecx
endif
    cmp     ecx,edx
    ja      end_loop
zero_found:
    xor     eax,eax
end_loop:
ifdef __AVX__
    vzeroupper
endif
    ret

endif ; __SSE__

ifdef USE_BYTECOPY

byte_scan:

ifdef _UNICODE
    movzx   ecx,word ptr [rax]
    cmp     ecx,edx
    je      toend
    test    ecx,ecx
    je      null
    movzx   ecx,word ptr [rax+2]
    cmp     ecx,edx
    je      one
    test    ecx,ecx
    je      null
    movzx   ecx,word ptr [rax+4]
    cmp     ecx,edx
    je      two
    add     rax,6
    test    ecx,ecx
else
    cmp     dl,[rax]
    je      toend
    cmp     dh,[rax]
    je      null
    cmp     dl,[rax+1]
    je      one
    cmp     dh,[rax+1]
    je      null
    cmp     dl,[rax+2]
    je      two
    add     rax,3
    cmp     dh,[rax-1]
endif
    jnz     byte_scan
null:
    xor     eax,eax
    ret
two:
    add     rax,tchar_t
one:
    add     rax,tchar_t
toend:
    ret
endif
    endp

    end
