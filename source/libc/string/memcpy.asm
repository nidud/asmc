; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

memcpy proc dst:ptr, src:ptr, size:size_t

ifdef __SSE__

ifdef _WIN64

    define reg <r8>
    define rdb <r8b>
    define rd1 <r9>
    define rd2 <r10>

else

    push esi
    push edi
    push ebx

    define reg <esi>
    define rdb <esi>
    define rd1 <edi>
    define rd2 <ebx>

endif

    ldr     reg,size
    ldr     rcx,dst
    ldr     rdx,src
    mov     rax,rcx

ifdef __AVX__

    cmp     reg,64
    ja      .64
    test    rdb,0x60
    jnz     .32

else

    cmp     reg,32
    ja      .32

endif

    test    rdb,0x30
    jnz     .16
    test    rdb,0x08
    jnz     .08
    test    rdb,0x04
    jnz     .04
    test    rdb,0x02
    jnz     .02
    test    rdb,0x01
    jnz     .01
    jmp     .3
.01:
    mov     cl,[rdx]
    mov     [rax],cl
    jmp     .3
.02:
    mov     cx,[rdx]
    mov     dx,[rdx+reg-2]
    mov     [rax+reg-2],dx
    mov     [rax],cx
    jmp     .3
.04:
    mov     ecx,[rdx]
    mov     edx,[rdx+reg-4]
    mov     [rax+reg-4],edx
    mov     [rax],ecx
    jmp     .3
.08:
    mov     rcx,[rdx]
    mov     rdx,[rdx+reg-8]
    mov     [rax],rcx
    mov     [rax+reg-8],rdx
    jmp     .3
.16:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+reg-16]
    movups  [rax],xmm0
    movups  [rax+reg-16],xmm1
    jmp     .3
.32:

ifdef __AVX__

    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+reg-32]
    vmovups [rax],ymm0
    vmovups [rax+reg-32],ymm1
    vzeroupper
    jmp     .3
.64:
    vmovups ymm2,[rdx]
    vmovups ymm3,[rdx+32]
    vmovups ymm4,[rdx+reg-32]
    vmovups ymm5,[rdx+reg-64]
    cmp     reg,128
    jbe     .2
    mov     rd2,-64
    mov     ecx,eax
    neg     ecx
    and     ecx,64-1
    add     rdx,rcx
    mov     rd1,reg
    sub     rd1,rcx
    add     rcx,rax
    and     rd1,rd2
    cmp     rcx,rdx
    ja     .1
    lea     rcx,[rcx+rd1-64]
    lea     rdx,[rdx+rd1-64]
    neg     rd2
    neg     rd1
.1:
    add     rd1,rd2
    vmovups ymm0,[rdx+rd1]
    vmovups ymm1,[rdx+rd1+32]
    vmovaps [rcx+rd1],ymm0
    vmovaps [rcx+rd1+32],ymm1
    jnz     .1
.2:
    vmovups [rax],ymm2
    vmovups [rax+32],ymm3
    vmovups [rax+reg-32],ymm4
    vmovups [rax+reg-64],ymm5
    vzeroupper

else

    movups xmm2,[rdx]
    movups xmm3,[rdx+16]
    movups xmm4,[rdx+reg-16]
    movups xmm5,[rdx+reg-32]
    cmp     reg,64
    jbe     .2
    mov     rd2,-32
    movzx   ecx,al
    neg     ecx
    and     ecx,32-1
    add     rdx,rcx
    mov     rd1,reg
    sub     rd1,rcx
    add     rcx,rax
    and     rd1,rd2
    cmp     rcx,rdx
    ja     .1
    lea     rcx,[rcx+rd1-32]
    lea     rdx,[rdx+rd1-32]
    neg     rd2
    neg     rd1
.1:
    add     rd1,rd2
    movups xmm0,[rdx+rd1]
    movups xmm1,[rdx+rd1+16]
    movaps [rcx+rd1],xmm0
    movaps [rcx+rd1+16],xmm1
    jnz     .1
.2:
    movups [rax],xmm2
    movups [rax+16],xmm3
    movups [rax+reg-16],xmm4
    movups [rax+reg-32],xmm5

endif

.3:
ifndef _WIN64
    pop     ebx
    pop     edi
    pop     esi
endif
    ret

else

ifdef _WIN64
ifdef __UNIX__
    mov     rax,rdi
    mov     rcx,rdx
else
    mov     r9,rdi
    mov     rax,rcx
    mov     rdi,rcx
    mov     rcx,r8
    xchg    rsi,rdx
endif
else
    push    esi
    mov     edx,edi
    mov     eax,dst
    mov     esi,src
    mov     ecx,size
    mov     edi,eax
endif

    cmp     rax,rsi
    ja      .0
    rep     movsb
    jmp     .1
.0:
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
.1:
ifdef _WIN64
ifndef __UNIX__
    mov     rsi,rdx
    mov     rdi,r9
endif
else
    mov     edi,edx
    pop     esi
endif
    ret

endif

memcpy endp

    end
