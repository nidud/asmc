; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

memcpy proc dst:ptr, src:ptr, size:size_t

if defined(_AMD64_) and defined(__AVX__)

    ldr     r8,size
    ldr     rcx,dst
    ldr     rdx,src

    mov     rax,rcx
    cmp     r8,64
    ja      .64
    test    r8b,0x60
    jnz     .32
    test    r8b,0x10
    jnz     .16
    test    r8b,0x08
    jnz     .08
    test    r8b,0x04
    jnz     .04
    test    r8b,0x02
    jnz     .02
    test    r8b,0x01
    jnz     .01
    jmp     .3
.01:
    mov     cl,[rdx]
    mov     [rax],cl
    jmp     .3
.02:
    mov     cx,[rdx]
    mov     dx,[rdx+r8-2]
    mov     [rax+r8-2],dx
    mov     [rax],cx
    jmp     .3
.04:
    mov     ecx,[rdx]
    mov     edx,[rdx+r8-4]
    mov     [rax+r8-4],edx
    mov     [rax],ecx
    jmp     .3
.08:
    mov     rcx,[rdx]
    mov     rdx,[rdx+r8-8]
    mov     [rax],rcx
    mov     [rax+r8-8],rdx
    jmp     .3
.16:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+r8-16]
    movups  [rax],xmm0
    movups  [rax+r8-16],xmm1
    jmp     .3
.32:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+r8-32]
    vmovups [rax],ymm0
    vmovups [rax+r8-32],ymm1
    vzeroupper
    jmp     .3
.64:
    vmovups ymm2,[rdx]
    vmovups ymm3,[rdx+32]
    vmovups ymm4,[rdx+r8-32]
    vmovups ymm5,[rdx+r8-64]
    cmp     r8,128
    jbe     .2
    mov     r10,-64
    mov     ecx,eax
    neg     ecx
    and     ecx,64-1
    add     rdx,rcx
    mov     r9,r8
    sub     r9,rcx
    add     rcx,rax
    and     r9b,r10b
    cmp     rcx,rdx
    ja     .1
    lea     rcx,[rcx+r9-64]
    lea     rdx,[rdx+r9-64]
    neg     r10
    neg     r9
.1:
    add     r9,r10
    vmovups ymm0,[rdx+r9]
    vmovups ymm1,[rdx+r9+32]
    vmovaps [rcx+r9],ymm0
    vmovaps [rcx+r9+32],ymm1
    jnz     .1
.2:
    vmovups [rax],ymm2
    vmovups [rax+32],ymm3
    vmovups [rax+r8-32],ymm4
    vmovups [rax+r8-64],ymm5
    vzeroupper
.3:

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

endif
    ret

memcpy endp

    end
