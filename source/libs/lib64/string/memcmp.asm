; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

memcmp::

    xchg rsi,rdx
    xchg rdi,rcx
    xchg rcx,r8
    xor  rax,rax
    repe cmpsb
    .ifnz
        sbb al,al
        sbb al,-1
    .endif
    mov rdi,r8
    mov rsi,rdx
    ret

    END
