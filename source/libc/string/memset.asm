; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *memset(char *dst, char value, size_t count);
;

include libc.inc

.code

memset proc

ifdef __SSE__

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
    mov     r9,rcx
    movzx   edx,dl
    mov     rcx,r8
endif
ifdef _WIN64
    mov     r10,0x0101010101010101
    imul    rdx,r10
else
    imul    edx,edx,0x01010101
endif
    cmp     rcx,16
    jae     above_16
    cmp     ecx,8
    jae     set_8
    cmp     ecx,4
    jae     set_4
    cmp     ecx,2
    jae     set_2
    test    ecx,ecx
    jz      set_0
set_1:
    mov     [rax],dl
set_0:
    ret
set_2:
    mov     [rax],dx
    mov     [rax+rcx-2],dx
    ret
set_4:
    mov     [rax],edx
    mov     [rax+rcx-4],edx
    ret
set_8:
    mov     [rax],rdx
ifndef _WIN64
    mov     [rax+4],edx
    mov     [rax+rcx-4],edx
endif
    mov     [rax+rcx-8],rdx
    ret

above_16:
ifdef __AVX512__
    vpbroadcastd zmm0,edx
else
    movd    xmm0,edx
ifdef __AVX__
    vbroadcastss ymm0,xmm0
else
    pshufd  xmm0,xmm0,0
endif
endif
    cmp     rcx,U*2
    ja      above_2U
ifdef __AVX512__
    cmp     ecx,64
    jae     set_80
endif
ifdef __AVX__
    cmp     ecx,32
    jae     set_40
endif
    cmp     ecx,16
    jae     set_20
set_10:
    mov     [rax],rdx
    mov     [rax+rcx-8],rdx
ifndef _WIN64
    mov     [rax+4],edx
    mov     [rax+rcx-4],edx
endif
    ret
set_20:
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm0
    ret
ifdef __AVX__
set_40:
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm0
    vzeroupper
    ret
endif
ifdef __AVX512__
set_80:
    vmovups [rax],zmm0
    vmovups [rax+rcx-64],zmm0
    vzeroupper
    ret
endif

above_2U:

ifdef __AVX512__
    vmovups [rax],zmm0
    vmovups [rax+rcx-64],zmm0
elseifdef __AVX__
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm0
else
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm0
endif
    add     rcx,rax
    and     al,-U
    add     rax,U
    sub     rcx,rax
    mov     rdx,rcx
    shr     rdx,(bsf U) + 2
    jz      set_U
    and     ecx,U*4-1
    ALIGN   size_t
loop_U4:
ifdef __AVX512__
    vmovaps [rax+U*0],zmm0
    vmovaps [rax+U*1],zmm0
    vmovaps [rax+U*2],zmm0
    vmovaps [rax+U*3],zmm0
elseifdef __AVX__
    vmovaps [rax+U*0],ymm0
    vmovaps [rax+U*1],ymm0
    vmovaps [rax+U*2],ymm0
    vmovaps [rax+U*3],ymm0
else
    movaps  [rax+U*0],xmm0
    movaps  [rax+U*1],xmm0
    movaps  [rax+U*2],xmm0
    movaps  [rax+U*3],xmm0
endif
    add     rax,U*4
    dec     rdx
    jnz     loop_U4
set_U:
    shr     rcx,bsf U
    jz      toend
    ALIGN   size_t
loop_U:
ifdef __AVX512__
    vmovaps [rax],zmm0
elseifdef __AVX__
    vmovaps [rax],ymm0
else
    movaps  [rax],xmm0
endif
    add     rax,U
    dec     rcx
    jnz     loop_U
toend:
ifndef _WIN64
    mov     eax,[esp+4]
elseifdef __UNIX__
    mov     rax,rdi
else
    mov     rax,r9
endif
ifdef __AVX__
    vzeroupper
endif
    ret

else ; __SSE__

    mov     edx,[esp+4]
    mov     eax,[esp+8]
    mov     ecx,[esp+12]
    xchg    edx,edi
    rep     stosb
    mov     edi,edx
    mov     eax,[esp+4]
    ret
endif
    endp
    end
