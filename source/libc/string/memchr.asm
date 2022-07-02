; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memchr proc p:ptr, c:int_t, count:size_t

ifdef _WIN64
    xchg    rcx,rdi
    xchg    rcx,r8
    mov     eax,edx
    repnz   scasb
    lea     rax,[rdi-1]
    mov     rdi,r8
else
    mov     edx,edi
    mov     ecx,count
    mov     edi,p
    mov     eax,c
    repnz   scasb
    lea     eax,[edi-1]
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

memchr endp

    end
