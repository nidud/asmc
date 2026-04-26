; _TCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include tchar.inc
include isa_availability.inc

option dotname

.code

_tcscpy::

ifndef _WIN64
    define  dst <[esp+4]>
    define  src <[esp+8]>
elseifdef __UNIX__
    define  dst <rdi>
    define  src <rsi>
else
    mov     r10,rcx
    define  dst <r10>
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
else
ifdef __AVX__
define tcmpeq vpcmpeqb
else
define tcmpeq pcmpeqb
endif
endif

ifndef src
    mov         r11,rdx
    mov         rcx,rdx
    define      src <r11>
else
    mov         rcx,src
endif
    mov         rax,src
ifdef _UNICODE
    test        al,1
    jnz         .byte_copy
endif

ifdef __AVX__
ifdef __TEST__
    mov         edx,0
    inc         edx
else
    test        __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz          .byte_copy
    and         al,-CHUNK
    and         cl,CHUNK-1
    or          edx,-1
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
    tcmpeq      ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
else
    and         al,-CHUNK
    and         cl,CHUNK-1
    mov         edx,-1
    shl         edx,cl
    pxor        xmm0,xmm0
    tcmpeq      xmm0,[rax]
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
endif
    add         rax,CHUNK
    and         ecx,edx
    jnz         .tail_bytes
    mov         rdx,rax
    sub         rdx,src
    add         rdx,dst

    align       size_t
.main_loop:
ifdef __AVX__
    vmovaps     ymm2,[rax]
    tcmpeq      ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
else
    movaps      xmm1,[rax]
    movaps      xmm2,[rax]
    tcmpeq      xmm1,xmm0
    pmovmskb    ecx,xmm1
endif
    add         rax,CHUNK
    test        ecx,ecx
    jnz         .tail_bytes
ifdef __AVX__
    vmovups     [rdx],ymm2
else
    movups      [rdx],xmm2
endif
    add         rdx,CHUNK
    jmp         .main_loop

.tail_bytes:
    mov         rdx,src
    bsf         ecx,ecx
    lea         rcx,[rax+rcx-CHUNK+TCHAR]
    sub         rcx,rdx
    mov         rax,dst
ifdef __AVX__
    cmp         ecx,32
    jae         .copy_64
    test        cl,0x30
    jnz         .copy_32
else
    cmp         ecx,16
    jae         .copy_32
endif
    test        cl,8
    jnz         .copy_16
    test        cl,4
    jnz         .copy_8
    cmp         cl,2
    jb          .copy_1
    je          .copy_2
.copy_3:
    mov         cl,[rdx+2]
    mov         [rax+2],cl
.copy_2:
    mov         cl,[rdx+1]
    mov         [rax+1],cl
.copy_1:
    mov         cl,[rdx]
    mov         [rax],cl
    ret

.copy_8:
ifdef _WIN64
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [rax],r8d
    mov         [rax+rcx-4],edx
else
    movss       xmm0,[rdx]
    movss       xmm1,[rdx+rcx-4]
    movss       [rax],xmm0
    movss       [rax+rcx-4],xmm1
endif
    ret

.copy_16:
ifdef _WIN64
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [rax],r8
    mov         [rax+rcx-8],rdx
else
    movsd       xmm0,[rdx]
    movsd       xmm1,[rdx+rcx-8]
    movsd       [rax],xmm0
    movsd       [rax+rcx-8],xmm1
endif
    ret

.copy_32:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [rax],xmm0
    movups      [rax+rcx-16],xmm1
    ret

ifdef __AVX__
.copy_64:
    vmovups     ymm0,[rdx]
    vmovups     ymm1,[rdx+rcx-32]
    vmovups     [rax],ymm0
    vmovups     [rax+rcx-32],ymm1
    ret
endif

endif

if defined(_UNICODE) or defined(__AVX__) or not defined(__SSE__)

.byte_copy:

ifdef src
    mov     rcx,dst
    mov     rdx,src
endif

.tbyte_copy:
    mov     _tal,[rdx]
    mov     [rcx],_tal
    add     rdx,tchar_t
    add     rcx,tchar_t
    test    _tal,_tal
    jnz     .tbyte_copy
    mov     rax,dst
    ret
endif

    end
