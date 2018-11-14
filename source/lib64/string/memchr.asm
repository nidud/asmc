; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

memchr::

    xchg    rcx,rdi
    xchg    rcx,r8
    mov     eax,edx
    repnz   scasb
    lea     rax,[rdi-1]
    mov     rdi,r8
    .ifnz
        xor eax,eax
    .endif
    ret

    END
