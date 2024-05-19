; WMEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wmemchr proc p:ptr, c:int_t, count:size_t

ifdef _WIN64
    ldr     rcx,p
    ldr     r8,count
    ldr     edx,c
    xchg    rcx,rdi
    xchg    rcx,r8
    mov     eax,edx
    repnz   scasw
    lea     rax,[rdi-2]
    mov     rdi,r8
else
    mov     edx,edi
    mov     ecx,count
    mov     edi,p
    mov     eax,c
    repnz   scasw
    lea     eax,[edi-2]
    mov     edi,edx
endif
ifdef __SSE__
    cmovnz  rax,rcx
else
    .ifnz
        mov rax,rcx
    .endif
endif
    ret

wmemchr endp

    end
