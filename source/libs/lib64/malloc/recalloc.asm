; RECALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winheap.inc
include internal.inc

_FREE   equ 0
_LOCAL  equ 1
_GLOBAL equ 2

    .code

_recalloc_base proc uses rsi rdi memblock:ptr, count:size_t, newsize:size_t

  local retp:ptr_t, size_orig:size_t, old_size:size_t

    xor eax,eax
    mov retp,rax
    mov size_orig,rax
    mov old_size,rax

    .repeat

        ;; ensure that (size * count) does not overflow
        .if rdx

            mov r9,rdx
            mov rax,_HEAP_MAXREQ
            xor edx,edx
            div r9

            _VALIDATE_RETURN_NOEXC(rax >= r8, ENOMEM, NULL)
        .endif

        mov rax,count
        mul r8
        mov size_orig,rax

        .if (memblock != NULL)
            mov old_size,_msize(memblock)
        .endif
        mov retp,_realloc_base(memblock, size_orig)
        mov r8,size_orig
        .if (rax != NULL && old_size < r8)

            add rax,old_size
            sub r8,old_size
            memset (rax, 0, r8)
        .endif
        mov rax,retp

    .until 1
    ret

_recalloc_base endp

    end
