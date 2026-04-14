; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

option dotname

.code

memcmp proc a:ptr, b:ptr, count:size_t
ifdef _WIN64
ifdef __UNIX__
    mov     r8,rdx
    mov     rcx,rdi
    mov     rdx,rsi
endif
else
    push    esi
    push    edi
    mov     ecx,a
    mov     edx,b
    mov     esi,count
    define  r8 <esi>
    define  r9 <edi>
endif
    sub     rdx,rcx
    cmp     r8,size_t
    jb      .2
    test    cl,size_t-1
    jz      .1
    align   size_t*2
.0:
    mov     al,[rcx]
    cmp     al,[rcx+rdx]
    jne     .D
    inc     rcx
    dec     r8
    test    cl,size_t-1
    jne     .0
.1:
    mov     r9,r8
    shr     r9,size_t/4+1
    jnz     .5
.2:
    test    r8,r8
    jz      .4
.3:
    mov     al,[rcx]
    cmp     al,[rcx+rdx]
    jne     .D
    inc     rcx
    dec     r8
    jnz     .3
.4:
    xor     eax,eax
    jmp     .E
.5:
    shr     r9,2
    jz      .7
.6:
    mov     rax,[rcx]
    cmp     rax,[rcx+rdx]
    jne     .C
    mov     rax,[rcx+size_t]
    cmp     rax,[rcx+rdx+size_t]
    jne     .B
    mov     rax,[rcx+size_t*2]
    cmp     rax,[rcx+rdx+size_t*2]
    jne     .A
    mov     rax,[rcx+size_t*3]
    cmp     rax,[rcx+rdx+size_t*3]
    jne     .9
    add     rcx,size_t*4
    dec     r9
    jnz     .6
    and     r8,size_t*4-1
.7:
    mov     r9,r8
    shr     r9,size_t/4+1
    jz      .2
.8:
    mov     rax,[rcx]
    cmp     rax,[rcx+rdx]
    jne     .C
    add     rcx,size_t
    dec     r9
    jnz     .8
    and     r8,size_t-1
    jmp     .2
.9:
    add     rcx,size_t
.A:
    add     rcx,size_t
.B:
    add     rcx,size_t
.C:
    mov     rcx,[rdx+rcx]
    bswap   rax
    bswap   rcx
    cmp     rax,rcx
.D:
    sbb     rax,rax
    sbb     rax,-1
.E:
ifndef _WIN64
    pop     edi
    pop     esi
endif
    ret
    endp

    end
