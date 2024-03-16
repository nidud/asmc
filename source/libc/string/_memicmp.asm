; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc

    .code

    option dotname

ifdef _WIN64
_memicmp proc a:ptr, b:ptr, size:size_t
    mov     r10,_pclmap
else
_memicmp proc uses esi edi ebx a:ptr, b:ptr, size:size_t
    mov     esi,_pclmap
endif

    ldr     rax,size
    ldr     rcx,a
    ldr     rdx,b

    dec     rcx
    dec     rdx
.0:
    test    rax,rax
    jz      .1
    dec     rax
    inc     rdx
    inc     rcx
ifdef _WIN64
    movzx   r8d,byte ptr [rcx]
    movzx   r9d,byte ptr [rdx]
    mov     r8b,[r10+r8]
    cmp     r8b,[r10+r9]
else
    movzx   ebx,byte ptr [rcx]
    movzx   edi,byte ptr [rdx]
    mov     bl,[rsi+rbx]
    cmp     bl,[rsi+rdi]
endif
    je      .0
    sbb     rax,rax
    sbb     rax,-1
.1:
    ret

_memicmp endp

    end
