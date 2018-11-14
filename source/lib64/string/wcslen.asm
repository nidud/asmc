; WCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

wcslen::

    xor eax,eax
    mov rdx,rdi
    mov rdi,rcx
    or	rcx,-1
    repne scasw
    mov rdi,rdx
    not rcx
    dec rcx
    mov rax,rcx
    ret

    END
