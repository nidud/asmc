; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

calloc proc n:size_t, nsize:size_t

ifdef _WIN64
    mov rax,rcx
    mul rdx
else
    mov eax,n
    mul nsize
endif
    malloc( rax )
    ret

calloc endp

    end
