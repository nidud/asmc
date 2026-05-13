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

if defined(_UNICODE) or not defined(__SSE__)
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
endif

strcat_copy::

ifdef __SSE__
ifdef __AVX512__
    vxorps  zmm0,zmm0,zmm0
elseifdef __AVX__
    vxorps  ymm0,ymm0,ymm0
else
    xorps   xmm0,xmm0
endif
    mov     rax,rcx
    test    dl,U-1
    jz      main_loop

    mov     r8,rcx          ; test for zero overlapped
    mov     ecx,edx
    and     dl,-U           ; align source
    and     ecx,U-1         ; shift count

ifdef __AVX512__
    tcmpeq  k0,zmm0,[rdx]
    kmovq   rax,k0
ifdef _UNICODE
    shr     ecx,1           ; 32-bit mask
endif
elseifdef __AVX__
    tcmpeq  ymm1,ymm0,[rdx]
    vpmovmskb eax,ymm1
else
    tcmpeq  xmm0,[rdx]
    pmovmskb eax,xmm0
    xorps   xmm0,xmm0
endif

    shr     rax,cl          ; reset pointers
    mov     rcx,rax
    mov     rax,r8
    lea     r8,[rdx+U]      ; aligned offset
    mov     rdx,src
    test    rcx,rcx
    jnz     tail_bytes

ifdef __AVX512__            ; need a full block
    tcmpeq  k0,zmm0,[r8]
    kmovq   rcx,k0
elseifdef __AVX__
    tcmpeq  ymm0,ymm0,[r8]
    vpmovmskb ecx,ymm0
else
    tcmpeq  xmm0,[r8]
    pmovmskb ecx,xmm0
endif
    test    rcx,rcx         ; one block + 1..U-1
    jz      align_source
    bsf     rcx,rcx
    sub     r8,rdx
if defined(_UNICODE) and defined(__AVX512__)
    shr     r8,1
endif
    add     rcx,r8
    jmp     head_bytes

    ALIGN   size_t

align_source:               ; write overlap
ifdef __AVX512__
    vmovups zmm2,[rdx]      ; first block
    vmovaps zmm1,[r8]       ; first aligned block
    vmovups [rax],zmm2      ; safe to write
elseifdef __AVX__
    vmovups ymm2,[rdx]
    vmovaps ymm1,[r8]
    vmovups [rax],ymm2
else
    movups  xmm2,[rdx]
    movaps  xmm1,[r8]
    movups  [rax],xmm2
endif
    sub     rax,rdx         ; align pointers
    add     rax,r8
    mov     rdx,r8
    jmp     loop_entry      ; write first block

    ALIGN   size_t*2

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

loop_entry:

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

    ALIGN   size_t

tail_bytes:

    bsf     rcx,rcx

head_bytes:

if defined(_UNICODE) and defined(__AVX512__)
    lea     ecx,[rcx*2+2]
else
    add     ecx,TCHAR
endif

    cmp     rcx,8
    ja      above_8
    je      copy_08
    cmp     ecx,6
    ja      copy_07
    je      copy_06
    cmp     ecx,4
    ja      copy_05
    je      copy_04
    cmp     ecx,2
    ja      copy_03
    je      copy_02
    test    ecx,ecx
    jz      copy_00

copy_01:
    mov     cl,[rdx]
    mov     [rax],cl
copy_00:
    jmp     strcat_exit

copy_02:
    mov     cx,[rdx]
    mov     [rax],cx
    jmp     strcat_exit

copy_03:
    mov     cl,[rdx+2]
    mov     dx,[rdx]
    mov     [rax+2],cl
    mov     [rax],dx
    jmp     strcat_exit

copy_04:
    mov     ecx,[rdx]
    mov     [rax],ecx
    jmp     strcat_exit

copy_05:
    mov     cl,[rdx+4]
    mov     edx,[rdx]
    mov     [rax+4],cl
    mov     [rax],edx
    jmp     strcat_exit

copy_06:
    mov     cx,[rdx+4]
    mov     edx,[rdx]
    mov     [rax+4],cx
    mov     [rax],edx
    jmp     strcat_exit

copy_07:
    mov     ecx,[rdx+3]
    mov     edx,[rdx]
    mov     [rax+3],ecx
    mov     [rax],edx
    jmp     strcat_exit

copy_08:
    mov     rcx,[rdx]
ifndef _WIN64
    mov     edx,[rdx+4]
    mov     [rax+4],edx
endif
    mov     [rax],rcx
    jmp     strcat_exit

    ALIGN   4

above_8:

ifdef __AVX512BW__
    cmp     ecx,64
    jae     copy_80
endif
ifdef __AVX__
    cmp     ecx,32
    jae     copy_40
endif
    cmp     ecx,16
    jae     copy_20

copy_10:
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

    ALIGN   4
copy_20:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1

ifdef __AVX__
    jmp     strcat_exit
    ALIGN   4
copy_40:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+rcx-32]
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm1
endif

ifdef __AVX512BW__
    jmp     strcat_exit
    ALIGN   4
copy_80:
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
