; _TCSCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strcpy(char *, char *);
; char *strcat(char *, char *);
; wchar_t *wcscpy(wchar_t *, wchar_t *);
; wchar_t *wcscat(wchar_t *, wchar_t *);
;

include tchar.inc
include isa_availability.inc

if defined(_UNICODE) or defined(__AVX__) or not defined(__SSE__)
define USE_BYTECOPY
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

ifndef _WIN64
define  dst <[esp+8]>
define  src <[esp+12]>
define  r8  <esi>
define  r8d <esi>
elseifdef __UNIX__
define  dst <rdi>
define  src <rsi>
else
define  dst <r10>
define  src <r11>
endif

LEAF_ENTRY macro
ifndef _WIN64
    push    esi
    mov     ecx,dst
    mov     edx,src
elseifdef __UNIX__
    mov     rcx,dst
    mov     rdx,src
else
    mov     dst,rcx
    mov     src,rdx
endif
endm

.code

ifndef __TEST_STRCPY__

_tcscat proc

    LEAF_ENTRY

ifdef __SSE__

ifdef _UNICODE
    mov     al,cl ; Unicode strings must be aligned.
    or      al,dl ;
    test    al,1  ;
    jnz     strcat_byte_copy
endif

ifdef __AVX__
ifdef __TEST__
    mov     eax,0
    inc     eax
elseifdef __AVX512__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jnz     align_to_boundary
    jmp     strcat_byte_copy
    align   strcat_length_loop size_t
endif

align_to_boundary:
    mov     rax,rcx         ; test first block with overlap
    and     al,-U
    and     ecx,U-1         ; bytes to ignore
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
    shl     rdx,cl
    mov     rcx,rdx
    test    rdx,rdx         ; CL may be 0 here..
    jnz     strcat_end_loop
ifndef __AVX__
    align   size_t
endif
strcat_length_loop:
ifdef __AVX512__
    tcmpeq  k0,zmm0,[rax]
    kmovq   rcx,k0
elseifdef __AVX__
    tcmpeq  ymm1,ymm0,[rax]
    vpmovmskb ecx,ymm1
else
    xcmpeq  xmm0,[rax]
    pmovmskb ecx,xmm0
endif
    add     rax,U
    test    rcx,rcx
    jz      strcat_length_loop

strcat_end_loop:
    bsf     rcx,rcx
if defined(_UNICODE) and defined(__AVX512__)
    lea     rcx,[rax+rcx*2-U]
else
    lea     rcx,[rax+rcx-U]
endif
    mov     rdx,src
    jmp     strcat_copy

endif ; __SSE__


ifdef USE_BYTECOPY

strcat_byte_copy:
ifdef _UNICODE
    movzx   eax,word ptr [rcx]
    test    eax,eax
    jz      byte_copy
    add     rcx,2
    jmp     strcat_byte_copy
else
    test    cl,3
    jz      strcat_loop
strcat_align:
    mov     al,[rcx]
    test    al,al
    jz      strcat_byte_copy_end
    inc     rcx
    test    cl,3
    jnz     strcat_align
strcat_loop:
    mov     eax,[rcx]
    lea     edx,[rax-0x01010101]
    add     rcx,4
    not     eax
    and     edx,0x80808080
    and     edx,eax
    jz      strcat_loop
    mov     rdx,src
    not     eax
    sub     rcx,4
    test    al,al
    jz      strcat_byte_copy_end
    inc     rcx
    test    ah,ah
    jz      strcat_byte_copy_end
    inc     rcx
    test    eax,0x00FF0000
    jz      strcat_byte_copy_end
    inc     rcx
strcat_byte_copy_end:
    jmp     byte_copy
endif
endif
    ret
    endp

    align   size_t*2

endif ; __TEST_STRCPY__

_tcscpy proc

    LEAF_ENTRY

ifdef __SSE__
ifdef _UNICODE
    mov     al,cl ; Unicode strings must be aligned.
    or      al,dl ;
    test    al,1  ;
    jnz     byte_copy
endif
ifdef __AVX__
if defined(__TEST__) or defined(__TEST_STRCPY__)
    mov     eax,0
    inc     eax
elseifdef __AVX512__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
elseifdef __AVX__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz      byte_copy
endif
endif

strcat_copy::

ifdef __SSE__

    mov     r8,rcx          ; test for zero overlapped
    mov     cl,dl
    and     dl,-U
    and     cl,U-1
ifdef __AVX512__
    vxorps  zmm0,zmm0,zmm0
    tcmpeq  k0,zmm0,[rdx]
    kmovq   rax,k0
ifdef _UNICODE
    shr     ecx,1           ; 32-bit mask
endif
elseifdef __AVX__
    vxorps  ymm0,ymm0,ymm0
    tcmpeq  ymm1,ymm0,[rdx]
    vpmovmskb eax,ymm1
else
    xorps   xmm0,xmm0
    tcmpeq  xmm0,[rdx]
    pmovmskb eax,xmm0
    xorps   xmm0,xmm0
endif
    shr     rax,cl
    mov     rcx,rax
    mov     rax,r8
    mov     rdx,src
    test    rcx,rcx
    jnz     tail_bytes

    test    dl,U-1          ; if aligned we already tested the first block
    jz      main_loop

    mov     ecx,edx         ; test the next block
    neg     ecx
    and     ecx,U-1
ifdef __AVX512__
    tcmpeq  k0,zmm0,[rdx+rcx]
    kmovq   rcx,k0
elseifdef __AVX__
    tcmpeq  ymm1,ymm0,[rdx+rcx]
    vpmovmskb ecx,ymm1
else
    tcmpeq  xmm0,[rdx+rcx]
    pmovmskb ecx,xmm0
endif
    test    rcx,rcx
    jnz     head_bytes

ifdef __AVX512__
    vmovups zmm1,[rdx]
    vmovups [rax],zmm1
elseifdef __AVX__
    vmovups ymm1,[rdx]
    vmovups [rax],ymm1
else
    movups  xmm1,[rdx]
    movups  [rax],xmm1
endif
    sub     rax,rdx
    and     dl,-U
    add     rdx,U
    add     rax,rdx

    align   size_t
main_loop:
ifdef __AVX512__
    vmovaps zmm1,[rdx]
    tcmpeq  k0,zmm0,zmm1
    kmovq   rcx,k0
elseifdef __AVX__
    vmovaps ymm1,[rdx]
    tcmpeq  ymm0,ymm0,ymm1
    vpmovmskb ecx,ymm0
else
    movaps  xmm1,[rdx]
    tcmpeq  xmm0,xmm1
    pmovmskb ecx,xmm0
endif
    test    rcx,rcx
    jnz     tail_bytes
ifdef __AVX512__
    vmovups [rax],zmm1
elseifdef __AVX__
    vmovups [rax],ymm1
else
    movups  [rax],xmm1
endif
    add     rax,U
    add     rdx,U
    jmp     main_loop

head_bytes:
    bsf     rcx,rcx
    neg     edx
    and     edx,U-1
if defined(_UNICODE) and defined(__AVX512__)
    shr     edx,1
endif
    add     ecx,edx
    mov     rdx,src
    jmp     tail_bytes2

    align   size_t

tail_bytes:
    bsf     rcx,rcx
tail_bytes2:
if defined(_UNICODE) and defined(__AVX512__)
    lea     ecx,[rcx*2+2]
else
    add     ecx,TCHAR
endif
ifdef __AVX512__
    cmp     ecx,64
    jae     copy_128
    test    cl,-32
    jnz     copy_64
    test    cl,-16
    jnz     copy_32
elseifdef __AVX__
    cmp     ecx,32
    jae     copy_64
    test    cl,-16
    jnz     copy_32
else
    cmp     ecx,16
    jae     copy_32
endif
    test    cl,8
    jnz     copy_16
    test    cl,4
    jnz     copy_8
    cmp     cl,2
    jb      copy_1
    je      copy_2

copy_3:
    mov     cl,[rdx+2]
    mov     [rax+2],cl
copy_2:
    mov     cx,[rdx]
    mov     [rax],cx
    jmp     strcat_exit
copy_1:
    mov     cl,[rdx]
    mov     [rax],cl
    jmp     strcat_exit

copy_8:
ifdef _WIN64
    mov     r8d,[rdx]
    mov     edx,[rdx+rcx-4]
    mov     [rax],r8d
    mov     [rax+rcx-4],edx
else
    movss   xmm0,[rdx]
    movss   xmm1,[rdx+rcx-4]
    movss   [rax],xmm0
    movss   [rax+rcx-4],xmm1
endif
    jmp     strcat_exit

copy_16:
ifdef _WIN64
    mov     r8,[rdx]
    mov     rdx,[rdx+rcx-8]
    mov     [rax],r8
    mov     [rax+rcx-8],rdx
else
    movsd   xmm0,[rdx]
    movsd   xmm1,[rdx+rcx-8]
    movsd   [rax],xmm0
    movsd   [rax+rcx-8],xmm1
endif
    jmp     strcat_exit

copy_32:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1
    jmp     strcat_exit

ifdef __AVX__
copy_64:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+rcx-32]
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm1
    jmp     strcat_exit
endif

ifdef __AVX512__
copy_128:
    vmovups zmm0,[rdx]
    vmovups zmm1,[rdx+rcx-64]
    vmovups [rax],zmm0
    vmovups [rax+rcx-64],zmm1
endif

strcat_exit:
    mov     rax,dst
ifdef __AVX__
    vzeroupper
endif
ifndef _WIN64
    pop     esi
endif
    ret

endif ; __SSE__


ifdef USE_BYTECOPY

byte_copy::
    sub     rcx,rdx
ifdef _UNICODE
    align   size_t
copy_loop:
    movzx   eax,word ptr [rdx]
    mov     [rdx+rcx],ax
    add     rdx,2
    test    eax,eax
    jnz     copy_loop
else
    test    dl,3
    jz      loop_entrance
copy_align:
    mov     al,[rdx]
    mov     [rdx+rcx],al
    test    al,al
    jz      byte_exit
    inc     rdx
    test    dl,3
    jnz     copy_align
    jmp     loop_entrance
    align   size_t
copy_loop:
    not     eax
    mov     [rdx+rcx],eax
    add     rdx,4
loop_entrance:
    mov     eax,[rdx]
    lea     r8d,[rax-0x01010101]
    not     eax
    and     r8d,eax
    and     r8d,0x80808080
    jz      copy_loop
    not     eax
    test    al,al
    mov     [rdx+rcx],al
    jz      byte_exit
    add     rdx,4
    test    ah,ah
    mov     [rdx+rcx-3],ah
    jz      byte_exit
    shr     eax,16
    test    al,al
    mov     [rdx+rcx-2],al
    jz      byte_exit
    test    ah,ah
    mov     [rdx+rcx-1],ah
    jnz     loop_entrance
endif
byte_exit:
    mov     rax,dst
ifndef _WIN64
    pop     esi
endif
endif
    ret
    endp

    end
