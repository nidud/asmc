; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

.code

calloc proc uses rbx n:size_t, nsize:size_t
    ldr rcx,n
    ldr rax,nsize
    mul rcx
    mov rbx,rax
    .if malloc( rax )
        mov rcx,rbx
        mov rdx,rdi
        mov rbx,rax
        mov rdi,rax
        xor eax,eax
        rep stosb
        mov rdi,rdx
        mov rax,rbx
    .endif
    ret
    endp

    end
