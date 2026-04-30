; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *memset(char *dst, char value, size_t count);
;

include isa_availability.inc

.code

memset::

ifdef _WIN64
ifdef __UNIX__
    mov     rcx,rdx
    movzx   edx,sil
    mov     rax,rdi
else
    mov     rax,rcx
    movzx   edx,dl
    mov     rcx,r8
endif
elseifdef __SSE__
    mov     eax,[esp+4]
    movzx   edx,byte ptr [esp+8]
    mov     ecx,[esp+12]
endif

ifdef __SSE__

    imul    edx,edx,0x01010101
    cmp     rcx,32
    ja      set_32
    test    cl,0x30
    jnz     set_16to32
    test    cl,8
    jnz     set_8to15
    test    cl,4
    jnz     set_4to7
    test    cl,2
    jnz     set_2to3
    test    ecx,ecx
    jnz     set_1
    ret
set_2to3:
    mov     [rax+rcx-2],dx
set_1:
    mov     [rax],dl
    ret
set_16to32:
    mov     [rax+8],edx
    mov     [rax+12],edx
    mov     [rax+rcx-16],edx
    mov     [rax+rcx-12],edx
set_8to15:
    mov     [rax+4],edx
    mov     [rax+rcx-8],edx
set_4to7:
    mov     [rax],edx
    mov     [rax+rcx-4],edx
    ret

ifdef __AVX__
    align   set_avx size_t*2
else
    align   set_xmm size_t*2
endif
set_32:
    movd    xmm0,edx
    pshufd  xmm0,xmm0,0
    movups  [rax],xmm0
    movups  [rax+16],xmm0
    movups  [rax+rcx-32],xmm0
    movups  [rax+rcx-16],xmm0
    mov     edx,32
    sub     edx,eax
    and     edx,32-1
    sub     rcx,rdx
    add     rdx,rax
    shr     rcx,5
    jz      toend

ifdef __AVX__
ifndef __TEST__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
    jz      set_xmm
endif
    vperm2f128 ymm0,ymm0,ymm0,0
set_avx:
    vmovaps [rdx],ymm0
    dec     rcx
    jz      end_avx
    vmovaps [rdx+32],ymm0
    dec     rcx
    jz      end_avx
    vmovaps [rdx+64],ymm0
    dec     rcx
    jz      end_avx
    vmovaps [rdx+96],ymm0
    add     rdx,128
    dec     rcx
    jnz     set_avx
end_avx:
    ret
    align   size_t*2
endif
set_xmm:
    movaps  [rdx],xmm0
    movaps  [rdx+16],xmm0
    add     rdx,32
    dec     rcx
    jnz     set_xmm
toend:
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
    end
