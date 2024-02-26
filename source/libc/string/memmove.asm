; MEMMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

memmove proc dst:ptr, src:ptr, count:size_t

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
    mov     ecx,count
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

memmove endp

    end
