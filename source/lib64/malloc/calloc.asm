; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

    option win64:nosave

calloc proc n:size_t, nsize:size_t

    mov rax,rcx
    mul rdx
    malloc( eax )
    ret

calloc endp

    end
