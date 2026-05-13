; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

ifdef __AVX512BW__
define U 64
elseifdef __AVX__
define U 32
elseifdef __SSE__
define U 16
else
define U size_t
endif

ALIAS <memmove>=<memcpy>

.code

memcpy proc

ifndef _WIN64
define r8   <esi>
define dst  <[esp+4]>
    mov     eax,[esp+4]
    mov     edx,[esp+8]
    mov     ecx,[esp+12]
elseifdef __UNIX__
define dst  <rdi>
    mov     rax,rdi
    mov     rcx,rdx
    mov     rdx,rsi
else
define dst  <r10>
    mov     rax,rcx
    mov     rcx,r8
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
    ret

copy_02:
    mov     cx,[rdx]
    mov     [rax],cx
    ret

copy_03:
    mov     cl,[rdx+2]
    mov     dx,[rdx]
    mov     [rax+2],cl
    mov     [rax],dx
    ret

copy_04:
    mov     ecx,[rdx]
    mov     [rax],ecx
    ret

copy_05:
    mov     cl,[rdx+4]
    mov     edx,[rdx]
    mov     [rax+4],cl
    mov     [rax],edx
    ret

copy_06:
    mov     cx,[rdx+4]
    mov     edx,[rdx]
    mov     [rax+4],cx
    mov     [rax],edx
    ret

copy_07:
    mov     ecx,[rdx+3]
    mov     edx,[rdx]
    mov     [rax+3],ecx
    mov     [rax],edx
    ret

copy_08:
    mov     rcx,[rdx]
ifndef _WIN64
    mov     edx,[rdx+4]
    mov     [rax+4],edx
endif
    mov     [rax],rcx
    ret

    ALIGN   4
above_8:
ifdef __SSE__
    cmp     rcx,U*2
    ja      begin_copy
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
    ret
    ALIGN   4
copy_20:
    movups  xmm0,[rdx]
    movups  xmm1,[rdx+rcx-16]
    movups  [rax],xmm0
    movups  [rax+rcx-16],xmm1
    ret
ifdef __AVX__
    ALIGN   4
copy_40:
    vmovups ymm0,[rdx]
    vmovups ymm1,[rdx+rcx-32]
    vmovups [rax],ymm0
    vmovups [rax+rcx-32],ymm1
    ret
endif
ifdef __AVX512BW__
    ALIGN   4
copy_80:
    vmovups zmm0,[rdx]
    vmovups zmm1,[rdx+rcx-64]
    vmovups [rax],zmm0
    vmovups [rax+rcx-64],zmm1
    ret
endif

    ALIGN   4

begin_copy:

ifndef _WIN64
    push    esi             ; r8 in 32-bit
elseifndef __UNIX__
    mov     dst,rax         ; save rcx in Win64
endif
    lea     r8,[rdx+rcx]    ; test overlap
    sub     rdx,rax
    jae     copy_up
    cmp     r8,rax
    ja      copy_down

copy_up:

ifdef __AVX512BW__
    vmovups zmm0,[rax+rdx]
elseifdef __AVX__
    vmovups ymm0,[rax+rdx]
else
    movups  xmm0,[rax+rdx]
endif

    mov     r8,rax
    add     rax,U
    test    al,U-1
    jz      check_blocks

    and     al,-U
ifdef __AVX512BW__
    vmovups zmm1,[rax+rdx]
    vmovups [r8],zmm0
    vmovaps zmm0,zmm1
elseifdef __AVX__
    vmovups ymm1,[rax+rdx]
    vmovups [r8],ymm0
    vmovaps ymm0,ymm1
else
    movups  xmm1,[rax+rdx]
    movups  [r8],xmm0
    movaps  xmm0,xmm1
endif
    add     rax,U

check_blocks:
    add     rcx,r8
    sub     rcx,rax
    mov     r8,rcx
    shr     r8,(bsf U) + 2 ; 64/128/256 byte block count
    jz      copy_u
    and     ecx,U*4-1
    jmp     loop_u4

    ALIGN   size_t*2

loop_u4:
ifdef __AVX512BW__
    vmovups zmm1,[rax+rdx+U*0]
    vmovups zmm2,[rax+rdx+U*1]
    vmovups zmm3,[rax+rdx+U*2]
    vmovups zmm4,[rax+rdx+U*3]
    vmovaps [rax-U],zmm0
    vmovaps [rax],zmm1
    vmovaps [rax+U],zmm2
    vmovaps [rax+U*2],zmm3
    vmovaps zmm0,zmm4
elseifdef __AVX__
    vmovups ymm1,[rax+rdx+U*0]
    vmovups ymm2,[rax+rdx+U*1]
    vmovups ymm3,[rax+rdx+U*2]
    vmovups ymm4,[rax+rdx+U*3]
    vmovaps [rax-U],ymm0
    vmovaps [rax],ymm1
    vmovaps [rax+U],ymm2
    vmovaps [rax+U*2],ymm3
    vmovaps ymm0,ymm4
else
    movups  xmm1,[rax+rdx+U*0]
    movups  xmm2,[rax+rdx+U*1]
    movups  xmm3,[rax+rdx+U*2]
    movups  xmm4,[rax+rdx+U*3]
    movaps  [rax-U],xmm0
    movaps  [rax],xmm1
    movaps  [rax+U],xmm2
    movaps  [rax+U*2],xmm3
    movaps  xmm0,xmm4
endif
    add     rax,U*4
    dec     r8
    jnz     loop_u4
    and     ecx,U*4-1

copy_u:
    mov     r8,rcx
    shr     r8,bsf U
    jz      end_copy_up

    ALIGN   4
loop_u:
ifdef __AVX512BW__
    vmovaps [rax-U],zmm0
    vmovups zmm0,[rax+rdx]
elseifdef __AVX__
    vmovaps [rax-U],ymm0
    vmovups ymm0,[rax+rdx]
else
    movaps  [rax-U],xmm0
    movups  xmm0,[rax+rdx]
endif
    add     rax,U
    dec     r8
    jnz     loop_u

end_copy_up:
    sub     rax,U
    and     ecx,U-1
    jz      count_aligned
    add     rcx,rax
end_copy:
ifdef __AVX512BW__
    vmovups zmm1,[rcx+rdx]
    vmovups [rcx],zmm1
count_aligned:
    vmovups [rax],zmm0
elseifdef __AVX__
    vmovups ymm1,[rcx+rdx]
    vmovups [rcx],ymm1
count_aligned:
    vmovups [rax],ymm0
else
    movups  xmm1,[rcx+rdx]
    movups  [rcx],xmm1
count_aligned:
    movups  [rax],xmm0
endif
ifndef _WIN64
    pop     esi
endif
ifdef __AVX__
    vzeroupper
endif
    mov     rax,dst
    ret

    ALIGN   4
copy_down:
    add     rax,rcx
ifdef __AVX512BW__
    vmovups zmm0,[rax+rdx-U]    ; read tail bytes
elseifdef __AVX__
    vmovups ymm0,[rax+rdx-U]
else
    movups  xmm0,[rax+rdx-U]
endif
    sub     rax,U
    sub     rcx,U
    test    al,U-1
    jz      dest_aligned2
    mov     r8,rax
    and     al,-U
ifdef __AVX512BW__
    vmovups zmm1,[rax+rdx]
    vmovups [r8],zmm0
    vmovaps zmm0,zmm1
elseifdef __AVX__
    vmovups ymm1,[rax+rdx]
    vmovups [r8],ymm0
    vmovaps ymm0,ymm1
else
    movups  xmm1,[rax+rdx]
    movups  [r8],xmm0
    movaps  xmm0,xmm1
endif
    add     rcx,rax
    sub     rcx,r8
dest_aligned2:
    mov     r8,rcx
    shr     r8,(bsf U) + 2     ; 64/128/256 byte block count
    jz      copy_d
    and     ecx,U*4-1
    jmp     loop_d4

    ALIGN   size_t*2

loop_d4:
ifdef __AVX512BW__
    vmovups zmm1,[rax+rdx-U*1]
    vmovups zmm2,[rax+rdx-U*2]
    vmovups zmm3,[rax+rdx-U*3]
    vmovups zmm4,[rax+rdx-U*4]
    vmovaps [rax-U*0],zmm0
    vmovaps [rax-U*1],zmm1
    vmovaps [rax-U*2],zmm2
    vmovaps [rax-U*3],zmm3
    vmovaps zmm0,zmm4
elseifdef __AVX__
    vmovups ymm1,[rax+rdx-U*1]
    vmovups ymm2,[rax+rdx-U*2]
    vmovups ymm3,[rax+rdx-U*3]
    vmovups ymm4,[rax+rdx-U*4]
    vmovaps [rax-U*0],ymm0
    vmovaps [rax-U*1],ymm1
    vmovaps [rax-U*2],ymm2
    vmovaps [rax-U*3],ymm3
    vmovaps ymm0,ymm4
else
    movups  xmm1,[rax+rdx-U*1]
    movups  xmm2,[rax+rdx-U*2]
    movups  xmm3,[rax+rdx-U*3]
    movups  xmm4,[rax+rdx-U*4]
    movaps  [rax-U*0],xmm0
    movaps  [rax-U*1],xmm1
    movaps  [rax-U*2],xmm2
    movaps  [rax-U*3],xmm3
    movaps  xmm0,xmm4
endif
    sub     rax,U*4
    dec     r8
    jnz     loop_d4

copy_d:
    mov     r8,rcx
    shr     r8,bsf U
    jz      end_down

    ALIGN   4
loop_d:
ifdef __AVX512BW__
    vmovaps [rax],zmm0
    vmovups zmm0,[rax+rdx-U]
elseifdef __AVX__
    vmovaps [rax],ymm0
    vmovups ymm0,[rax+rdx-U]
else
    movaps  [rax],xmm0
    movups  xmm0,[rax+rdx-U]
endif
    sub     rax,U
    dec     r8
    jnz     loop_d

end_down:
    and     ecx,U-1
    jz      count_aligned
    sub     rcx,rax
    neg     rcx
    jmp     end_copy

else ; __SSE__

ifndef _LIN64
    xchg    rdx,rsi
    xchg    rax,rdi
endif
    cmp     rdi,rsi
    ja      copy_down
    rep     movsb
ifndef _LIN64
    mov     rsi,rdx
    mov     rdi,rax
    mov     rax,dst
endif
    ret
copy_down:
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
endif
    endp
    end
