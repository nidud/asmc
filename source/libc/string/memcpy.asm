; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include isa_availability.inc

ifdef __SSE__
ifdef __AVX__
if defined(__AVX512BW__) ;and defined(_WIN64)
define __AVX512__
define U 64
else
define U 32
endif
else
define U 16
endif
else
define U size_t
endif

ifndef _WIN64
define  dst <[esp+4]>
define  src <[esp+8]>
define  len <[esp+12]>
define  tmp <[esp+8]>
else
define  len <r8>
define  tmp <r9>
ifdef __UNIX__
define  dst <rdi>
define  src <rsi>
else
define  dst <r11>
define  src <r10>
endif
endif

ifndef __UNIX__
ALIAS <memmove>=<memcpy>
endif

.code

ifdef __UNIX__
memmove::
endif

memcpy proc

ifndef _WIN64
    mov     eax,dst
    mov     edx,src
    mov     ecx,len
elseifdef __UNIX__
    mov     rax,rdi
    mov     rcx,rdx
    mov     rdx,rsi
else
    mov     dst,rcx
    mov     rax,rcx
    mov     rcx,r8
endif
    cmp     rax,rdx
    jbe     non_overlapping_buffers
    sub     rax,rcx
    cmp     rax,rdx
    lea     rax,[rax+rcx]
    jb      overlapping_buffers

non_overlapping_buffers:

ifdef __AVX__
ifdef __TEST__
    test    rcx,rcx
elseifdef __AVX512__
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX512
else
    test    __isa_enabled,1 shl __ISA_AVAILABLE_AVX
endif
    jz      string_copy
endif

ifdef __SSE__

    cmp     rcx,U*2
    ja      begin_copy

ifdef __AVX512__
    test    cl,-64
    jnz     copy_64_128
endif

ifdef __AVX__
    test    cl,-32
    jnz     copy_32_64
endif

    test    cl,-16
    jnz     copy_16_32
    test    cl,-8
    jnz     copy_8_16
    test    cl,4
    jnz     copy_4_8
    cmp     cl,2
    je      copy_2
    ja      copy_3
    test    cl,cl
    je      copy_0

copy_1:
    mov     cl,[rdx]
    mov     [rax],cl
copy_0:
    ret

copy_3:
    mov     cl,[rdx+2]
    mov     dx,[rdx]
    mov     [rax+2],cl
    mov     [rax],dx
    ret

copy_2:
    mov     cx,[rdx]
    mov     [rax],cx
    ret

copy_4_8:
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
    ret

copy_8_16:
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
    ret

copy_16_32:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1
    ret

ifdef __AVX__
copy_32_64:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+rcx-32]
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm1
    vzeroupper
    ret
endif

ifdef __AVX512__
copy_64_128:
    vmovups zmm0,[rdx]
    vmovups zmm1,[rdx+rcx-64]
    vmovups [rax],zmm0
    vmovups [rax+rcx-64],zmm1
    vzeroupper
    ret
endif

    align   loop_u4 size_t*2    ; emit align bytes here

begin_copy:

ifdef __AVX512__
    vmovups zmm4,[rdx]          ; read head bytes
    vmovups zmm5,[rdx+rcx-U]    ; read tail bytes
elseifdef __AVX__
    vmovups ymm4,[rdx]
    vmovups ymm5,[rdx+rcx-U]
else
    movups  xmm4,[rdx]
    movups  xmm5,[rdx+rcx-U]
endif

    lea     rax,[rdx+U]         ; advance source
    and     al,-U               ; and align
    sub     rax,rdx             ; get size
    sub     rcx,rax             ; adjust count
    add     rdx,rax             ; adjust source
    add     rax,dst             ; adjust target

check_blocks:
    mov     tmp,rcx
    shr     rcx,(bsf U) + 2     ; 64/128/256 byte block count
    jz      copy_u

loop_u4:
ifdef __AVX512__
    vmovaps zmm0,[rdx+U*0]
    vmovaps zmm1,[rdx+U*1]
    vmovaps zmm2,[rdx+U*2]
    vmovaps zmm3,[rdx+U*3]
    vmovups [rax+U*0],zmm0
    vmovups [rax+U*1],zmm1
    vmovups [rax+U*2],zmm2
    vmovups [rax+U*3],zmm3
elseifdef __AVX__
    vmovaps ymm0,[rdx+U*0]
    vmovaps ymm1,[rdx+U*1]
    vmovaps ymm2,[rdx+U*2]
    vmovaps ymm3,[rdx+U*3]
    vmovups [rax+U*0],ymm0
    vmovups [rax+U*1],ymm1
    vmovups [rax+U*2],ymm2
    vmovups [rax+U*3],ymm3
else
    movaps  xmm0,[rdx+U*0]
    movaps  xmm1,[rdx+U*1]
    movaps  xmm2,[rdx+U*2]
    movaps  xmm3,[rdx+U*3]
    movups  [rax+U*0],xmm0
    movups  [rax+U*1],xmm1
    movups  [rax+U*2],xmm2
    movups  [rax+U*3],xmm3
endif
    add     rax,U*4
    add     rdx,U*4
    dec     rcx
    jnz     loop_u4

copy_u:
    mov     rcx,tmp             ; blocks left if any
    and     ecx,U*4-1
    shr     ecx,bsf U
    jz      end_copy

loop_u:
ifdef __AVX512__
    vmovaps zmm0,[rdx]
    vmovups [rax],zmm0
elseifdef __AVX__
    vmovaps ymm0,[rdx]
    vmovups [rax],ymm0
else
    movaps  xmm0,[rdx]
    movups  [rax],xmm0
endif
    add     rax,U
    add     rdx,U
    dec     rcx
    jnz     loop_u
end_copy:
    mov     rcx,len
    mov     rax,dst
ifdef __AVX512__
    vmovups [rax],zmm4          ; write head bytes
    vmovups [rax+rcx-U],zmm5    ; write tail bytes
    vzeroupper
elseifdef __AVX__
    vmovups [rax],ymm4
    vmovups [rax+rcx-U],ymm5
    vzeroupper
else
    movups  [rax],xmm4
    movups  [rax+rcx-U],xmm5
endif
    ret

endif ; __SSE__

string_copy:
ifndef _LIN64
    xchg    rdx,rsi
    xchg    rax,rdi
endif
    rep     movsb
ifndef _LIN64
    mov     rsi,rdx
    mov     rdi,rax
    mov     rax,dst
endif
    ret

overlapping_buffers:
ifndef _LIN64
    xchg    rdx,rsi
    xchg    rax,rdi
endif
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
ifndef _LIN64
    mov     rsi,rdx
    mov     rdi,rax
    mov     rax,dst
endif
    ret
    endp

    end
