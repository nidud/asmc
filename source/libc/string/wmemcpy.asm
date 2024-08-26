; WMEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

ifndef __UNIX__
undef wmemmove
ALIAS <wmemmove>=<wmemcpy>
endif

    .code

    option dotname

wmemcpy proc dst:ptr, src:ptr, size:size_t

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
    rep     movsw
    jmp     .1
.0:
    lea     rsi,[rsi+rcx-2]
    lea     rdi,[rdi+rcx-2]
    std
    rep     movsw
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

wmemcpy endp

ifdef __UNIX__
wmemmove proc dst:ptr, src:ptr, size:size_t
ifdef _WIN64
    wmemcpy(rdi, rsi, rdx)
else
    wmemcpy(dst, src, size)
endif
    ret
wmemmove endp
endif

    end
