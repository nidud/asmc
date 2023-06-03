; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

if defined(_AMD64_) and defined(__AVX__)

memmove::
memcpy::

ifdef __UNIX__
    mov     r8,rdx
    mov     rcx,rdi
    mov     rdx,rsi
endif
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
    ret
.01:
    mov     cl,[rdx]
    mov     [rax],cl
    ret
.02:
    mov     cx,[rdx]
    mov     dx,[rdx+r8-2]
    mov     [rax+r8-2],dx
    mov     [rax],cx
    ret
.04:
    mov     ecx,[rdx]
    mov     edx,[rdx+r8-4]
    mov     [rax+r8-4],edx
    mov     [rax],ecx
    ret
.08:
    mov     rcx,[rdx]
    mov     rdx,[rdx+r8-8]
    mov     [rax],rcx
    mov     [rax+r8-8],rdx
    ret
.16:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+r8-16]
    movups  [rax],xmm0
    movups  [rax+r8-16],xmm1
    ret
.32:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+r8-32]
    vmovups [rax],ymm0
    vmovups [rax+r8-32],ymm1
    vzeroupper
    ret
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
    ret

else

if defined(_AMD64_) and defined(__UNIX__)
memcpy proc dst:ptr, src:ptr, size:size_t
    mov rax,rdi
    mov rcx,rdx
else
memcpy proc uses rsi rdi dst:ptr, src:ptr, size:size_t
    ldr rax,dst
    ldr rsi,src
    ldr rcx,size
    mov rdi,rax
endif
    rep movsb
    ret

memcpy endp

endif

    end
