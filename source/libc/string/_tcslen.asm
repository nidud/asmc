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

_tcslen proc

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
    jnz     byte_length
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
    jz      byte_length
endif

align_to_boundary:

    and     al,-U
    and     cl,U-1
ifdef __AVX512__
    vxorps  zmm0,zmm0,zmm0
ifdef _UNICODE
    shr     ecx,1           ; 32-bit mask
endif
    tcmpeq  k0,zmm0,[rax]
    kmovq   rdx,k0
elseifdef __AVX__
    vxorps  ymm0,ymm0,ymm0
    tcmpeq  ymm1,ymm0,[rax]
    vpmovmskb edx,ymm1
else
    xorps   xmm0,xmm0
    xcmpeq  xmm0,[rax]
    pmovmskb edx,xmm0
    xorps   xmm0,xmm0
endif
    add     rax,U
    shr     rdx,cl          ; shift out low bits..
    shl     rdx,cl          ; CL may be 0 here..
    test    rdx,rdx
    jnz     toend

    align   size_t
main_loop:
ifdef __AVX512__
    tcmpeq  k0,zmm0,[rax]
    kmovq   rdx,k0
elseifdef __AVX__
    tcmpeq  ymm0,ymm0,[rax]
    vpmovmskb edx,ymm0
else
    xcmpeq  xmm0,[rax]
    pmovmskb edx,xmm0
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
ifdef __AVX__
    vzeroupper
endif
    ret

endif ; __SSE__

if defined(_UNICODE) or defined(__AVX__) or not defined(__SSE__)

byte_length:
ifdef _UNICODE
ifndef _LIN64
    mov     rdx,rdi
    mov     rdi,rcx
endif
    or      rcx,-1
    xor     eax,eax
    repnz   scasw
    mov     rax,rcx
ifndef _LIN64
    mov     rdi,rdx
endif
    not     rax
    dec     rax
else
    mov     rax,rcx
    test    al,3
    jz      byte_loop
byte_align:
    mov     dl,[rax]
    inc     rax
    test    dl,dl
    jz      return_byte_3
    test    al,3
    jnz     byte_align
byte_loop:
    mov     edx,[rax]
    lea     ecx,[rdx-0x01010101]
    add     rax,4
    not     edx
    and     ecx,edx
    and     ecx,0x80808080
    jz      byte_loop
    not     edx
    test    dl,dl
    jz      return_byte_0
    test    dh,dh
    jz      return_byte_1
    shr     edx,16
    test    dl,dl
    jz      return_byte_2
    test    dh,dh
    jz      return_byte_3
    jmp     byte_loop
return_byte_0:
    dec     rax
return_byte_1:
    dec     rax
return_byte_2:
    dec     rax
return_byte_3:
    dec     rax
    sub     rax,string
endif
    ret
endif
    endp
    end
