; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memchr proc p:ptr, c:int_t, count:size_t

    ldr     eax,c
if defined(_WIN64) and defined(__UNIX__)
    mov     rcx,rdx
    repnz   scasb
    lea     rax,[rdi-1]
else
    ldr     rdx,count
    ldr     rcx,p

    xchg    rcx,rdi
    xchg    rcx,rdx
    repnz   scasb
    lea     rax,[rdi-1]
    mov     rdi,rdx
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
