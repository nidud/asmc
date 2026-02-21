; _CPU_DISP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc
include isa_availability.inc

public __favor
public __isa_available
public __isa_enabled

option dotname

.data
 __favor            dd 0
ifdef _WIN64
 __isa_available    dd __ISA_AVAILABLE_SSE2
 __isa_enabled      dd 1 shl __ISA_AVAILABLE_SSE2
else
 __isa_available    dd __ISA_AVAILABLE_X86
 __isa_enabled      dd 1 shl __ISA_AVAILABLE_X86
endif

ifdef __P586__

.code

_cpu_disp proc uses rsi rdi rbx
ifndef _WIN64
    pushfd
    pop     eax
    mov     ecx,0x200000
    mov     edx,eax
    xor     eax,ecx
    push    eax
    popfd
    pushfd
    pop     eax
    xor     eax,edx
    and     eax,ecx
    jz      .4
endif
    xor     eax, eax
    xor     ecx, ecx
    cpuid
    mov     esi,eax
    xor     ebx,0x756E6547
    xor     ecx,0x6C65746E
    xor     edx,0x49656E69
    or      ebx,ecx
    xor     ecx,ecx
    or      ebx,edx
    mov     eax,1
    cpuid
    mov     edi,ecx
    jnz     .2
    and     eax,0xFFF3FF0
    cmp     eax,0x00106C0
    jz      .1
    cmp     eax,0x0020660
    jz      .1
    cmp     eax,0x0020670
    jz      .1
    cmp     eax,0x0030650
    jz      .1
    cmp     eax,0x0030660
    jz      .1
    cmp     eax,0x0030670
    jnz     .2
.1:
    or      __favor,1 shl __FAVOR_ATOM
.2:
    mov     eax,7
    cmp     esi,eax
    jl      .3
    xor     ecx, ecx
    cpuid
    bt      ebx,9
    jnc     .3
    or      __favor,1 shl __FAVOR_ENFSTRG
.3:
ifndef _WIN64
    mov     __isa_available,__ISA_AVAILABLE_SSE2
    mov     __isa_enabled,1 shl __ISA_AVAILABLE_SSE2
endif
    bt      edi,20
    jnc     .4
    mov     __isa_available,__ISA_AVAILABLE_SSE42
    or      __isa_enabled,1 shl __ISA_AVAILABLE_SSE42
ifdef __SSE__
    bt      edi,27
    jnc     .4
    bt      edi,28
    jnc     .4
    xor     ecx,ecx
    xgetbv
    mov     ecx,eax
    and     al,6
    cmp     al,6
    jnz     .4
    mov     __isa_available,__ISA_AVAILABLE_AVX
    or      __isa_enabled,1 shl __ISA_AVAILABLE_AVX
    test    bl,0x20
    jz      .4
    mov     __isa_available,__ISA_AVAILABLE_AVX2
    or      __isa_enabled,1 shl __ISA_AVAILABLE_AVX2
    and     ebx,0xD0030000
    cmp     ebx,0xD0030000
    jnz     .4
    and     cl,0xE0
    cmp     cl,0xE0
    jnz     .4
    mov     __isa_available,__ISA_AVAILABLE_AVX512
    or      __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
endif
.4:
    xor     eax,eax
    ret
    endp

.pragma init(_cpu_disp, 7)
endif
    end
