; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *memcmp(void *, void *, size_t);
;

include libc.inc

ifdef __AVX__
define U 16
else
define U size_t
endif

.code

memcmp proc

ifndef _WIN64
    push    esi
    push    edi
    mov     ecx,8[esp+4]
    mov     edx,8[esp+8]
    mov     esi,8[esp+12]
    define  r8 <esi>
    define  r9 <edi>
    define  r8d <esi>
elseifdef __UNIX__
    mov     r8,rdx
    mov     rcx,rdi
    mov     rdx,rsi
endif
    cmp     r8,U
    ja      align_to_boundary

remaining_bytes:

    test    r8,r8
    jz      equal

    mov     eax,r8d
    neg     eax
    and     eax,U-1
    sub     rcx,rax
    sub     rdx,rax
    shl     eax,3
if defined(__TEST__) and not defined(_WIN64)
    mov     r8,8[esp+16]
    add     r8,shorttable-memcmp
else
    lea     r8,shorttable
endif
    add     rax,r8
    jmp     rax

    align   8
shorttable:
UNIT = 0
while UNIT lt U
    mov     al,[rcx+UNIT]       ; 8 byte code blocks (4/8/16)
    cmp     al,[rdx+UNIT]
    jnz     not_equal
    align   8
    UNIT = UNIT + 1
    endm
equal:
    xor     eax,eax
ifndef _WIN64
    pop     edi
    pop     esi
endif
    ret
not_equal:
    sbb     eax,eax
    sbb     eax,-1
ifndef _WIN64
    pop     edi
    pop     esi
endif
    ret

align_to_boundary:

    test    cl,U-1
    jz      check_blocks

ifdef __AVX__
    movups  xmm0,[rcx]
    movups  xmm1,[rdx]
    pcmpeqb xmm0,xmm1
    pmovmskb eax,xmm0
    xor     eax,0xFFFF
else
    mov     rax,[rcx]
    cmp     rax,[rdx]
endif
    jnz     adjust_0

    mov     eax,ecx
    neg     eax
    and     eax,U-1
    sub     r8,rax
    add     rcx,rax
    add     rdx,rax

check_blocks:
    mov     r9,r8
    shr     r9,(bsf U) + 2      ; 16/32/64 byte block count
    jz      compare_u

loop_u4:
ifdef __AVX__
    vmovups ymm0,[rdx]
    vpcmpeqb ymm0,ymm0,[rcx]
    vpmovmskb eax,ymm0
    xor     eax,-1
    jnz     adjust_0
    vmovups  ymm0,[rdx+32]
    vpcmpeqb ymm0,ymm0,[rcx+32]
    vpmovmskb eax,ymm0
    xor     eax,-1
    jnz     adjust_2
else
    mov     rax,[rcx]
    cmp     rax,[rdx]
    jne     adjust_0
    mov     rax,[rcx+U]
    cmp     rax,[rdx+U]
    jne     adjust_1
    mov     rax,[rcx+U*2]
    cmp     rax,[rdx+U*2]
    jne     adjust_2
    mov     rax,[rcx+U*3]
    cmp     rax,[rdx+U*3]
    jne     adjust_3
endif
    add     rcx,U*4
    add     rdx,U*4
    dec     r9
    jnz     loop_u4
    and     r8,U*4-1

compare_u:
    mov     r9,r8
    shr     r9,bsf U
    jz      remaining_bytes

loop_u:
ifdef __AVX__
    movups  xmm0,[rdx]
    pcmpeqb xmm0,[rcx]
    pmovmskb eax,xmm0
    xor     eax,0xFFFF
else
    mov     rax,[rcx]
    cmp     rax,[rdx]
endif
    jne     adjust_0
    add     rcx,U
    add     rdx,U
    dec     r9
    jnz     loop_u
    and     r8,U-1
    jmp     remaining_bytes
ifdef __AVX__
adjust_2:
    add     rcx,U*2
    add     rdx,U*2
else
adjust_3:
    add     rdx,U
adjust_2:
    add     rdx,U
adjust_1:
    add     rdx,U
endif
adjust_0:
ifdef __AVX__
    bsf     eax,eax
    mov     cl,[rcx+rax]
    cmp     cl,[rdx+rax]
else
    mov     rcx,[rdx]
    bswap   rax
    bswap   rcx
    cmp     rax,rcx
endif
    jmp     not_equal
    endp

    end
