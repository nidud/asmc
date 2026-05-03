; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *memcpy(void *dst, void *src, size_t count);
; void *memmove(void *dst, void *src, size_t count);
;

include isa_availability.inc

.code

memcpy::
memmove::

ifndef _WIN64
    mov     eax,[esp+4]
    mov     edx,[esp+8]
    mov     ecx,[esp+12]
    define  r9  <[esp+16]>
    define  r10 <esi>
elseifdef __UNIX__
    mov     rcx,rdx
    mov     rax,rdi
    mov     rdx,rsi
else
    mov     rax,rcx
    mov     rcx,r8
endif

ifdef __SSE__

    cmp     rcx,64
    ja      copy_64
    test    cl,0x60
    jnz     copy_32to64
    test    cl,0x30
    jnz     copy_16to31
    test    cl,0x08
    jnz     copy_8to15
    test    cl,0x04
    jnz     copy_4to7
    cmp     cl,2
    ja      copy_3
    je      copy_2
    test    ecx,ecx
    jz      copy_0
copy_1:
    mov     cl,[rdx]
    mov     [rax],cl
copy_0:
    ret
copy_2:
    mov     cx,[rdx]
    mov     [rax],cx
    ret
copy_3:
    mov     cl,[rdx+2]
    mov     dx,[rdx]
    mov     [rax],dx
    mov     [rax+2],cl
    ret
copy_4to7:
ifdef _WIN64
    mov     r8d,[rdx]
    mov     r9d,[rdx+rcx-4]
    mov     [rax],r8d
    mov     [rax+rcx-4],r9d
else
    movss   xmm0,[rdx]
    movss   xmm1,[rdx+rcx-4]
    movss   [rax],xmm0
    movss   [rax+rcx-4],xmm1
endif
    ret
copy_8to15:
ifdef _WIN64
    mov     r8,[rdx]
    mov     r9,[rdx+rcx-8]
    mov     [rax],r8
    mov     [rax+rcx-8],r9
else
    movsd   xmm0,[rdx]
    movsd   xmm1,[rdx+rcx-8]
    movsd   [rax],xmm0
    movsd   [rax+rcx-8],xmm1
endif
    ret
copy_16to31:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1
    ret
copy_32to64:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+16]
    movups  xmm2,[rdx+rcx-32]
    movups  xmm3,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+16],xmm1
    movups  [rax+rcx-32],xmm2
    movups  [rax+rcx-16],xmm3
    ret

ifdef __AVX__

    align loop_avx size_t*2

copy_64:

ifndef __TEST__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
    jz      copy_gpr
endif
    vmovups ymm2,[rdx]              ; save 128 byte overlap
    vmovups ymm3,[rdx+32]
    vmovups ymm4,[rdx+rcx-64]
    vmovups ymm5,[rdx+rcx-32]

    cmp     rcx,128
    jbe     copy_128

ifdef _WIN64
    mov     r9,rax
    mov     r8,rcx
else
    push    esi
    push    ecx
    push    eax
endif
ifdef __UNIX__
    neg     eax                     ; alignment for System-V
else
    neg     rax
endif
    and     eax,64-1                ; aligned writes
    add     rdx,rax                 ; advance source pointer
    sub     rcx,rax                 ; adjust count
    add     rax,r9                  ; align dest to 64
    mov     r10,-64                 ; chunk size
    and     rcx,-64                 ; align count
    cmp     rax,rdx                 ; copy direction
    ja      loop_avx
    lea     rax,[rax+rcx-64]        ; flip direction
    lea     rdx,[rdx+rcx-64]
    neg     r10                     ; +
    neg     rcx                     ; -
loop_avx:
    add     rcx,r10                 ; copy aligned blocks
    vmovups ymm0,[rdx+rcx]
    vmovups ymm1,[rdx+rcx+32]
    vmovaps [rax+rcx],ymm0
    vmovaps [rax+rcx+32],ymm1
    jnz     loop_avx

ifdef _WIN64
    mov     rax,r9                  ; dest pointer = return value
    mov     rcx,r8                  ; reset count
else
    pop     eax
    pop     ecx
    pop     esi
endif

copy_128:
    vmovups [rax],ymm2              ; overlapping head and tail bytes
    vmovups [rax+32],ymm3
    vmovups [rax+rcx-64],ymm4
    vmovups [rax+rcx-32],ymm5
    vzeroupper
    ret

copy_gpr:

else

    align loop_xmm 8

copy_64:

    movups  xmm2,[rdx]              ; save 64 byte overlap
    movups  xmm3,[rdx+16]
    movups  xmm4,[rdx+rcx-32]
    movups  xmm5,[rdx+rcx-16]

ifdef _WIN64
ifdef __UNIX__
    mov     r8,rcx
endif
    mov     r9,rax
else
    push    esi
    push    ecx
    push    eax
endif
    neg     rax
    and     eax,32-1
    add     rdx,rax
    sub     rcx,rax
    add     rax,r9
    mov     r10,-32
    and     rcx,r10
    cmp     rax,rdx
    ja      loop_xmm
    lea     rax,[rax+rcx-32]
    lea     rdx,[rdx+rcx-32]
    neg     r10
    neg     rcx
loop_xmm:
    add     rcx,r10
    movups  xmm0,[rdx+rcx]
    movups  xmm1,[rdx+rcx+16]
    movaps  [rax+rcx],xmm0
    movaps  [rax+rcx+16],xmm1
    jnz     loop_xmm
ifdef _WIN64
    mov     rax,r9
    mov     rcx,r8
else
    pop     eax
    pop     ecx
    pop     esi
endif
    movups  [rax],xmm2
    movups  [rax+16],xmm3
    movups  [rax+rcx-32],xmm4
    movups  [rax+rcx-16],xmm5
    ret

endif
endif ; __SSE__

if defined(__AVX__) or not defined(__SSE__)

ifndef _WIN64
    push    esi
    push    edi
elseifndef __UNIX__
    mov     r8,rsi
    mov     r9,rdi
endif
    mov     rsi,rdx
    mov     rdi,rax
    cmp     rax,rdx
    ja      L1
    rep     movsb
    jmp     L2
L1:
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
L2:
ifndef _WIN64
    pop     edi
    pop     esi
elseifndef __UNIX__
    mov     rsi,r8
    mov     rdi,r9
endif
    ret
endif
    end
