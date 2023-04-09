; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

calloc proc n:size_t, nsize:size_t

    mov rax,rdi
    mul rsi
    malloc(rax)
    ret

calloc endp

    end
