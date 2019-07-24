; _ALIGNED_MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

_aligned_malloc proc uses rdi dwSize:size_t, Alignment:size_t

    mov rdi,rdx
    lea rcx,[rcx+rdx+sizeof(HEAP)]

    .if malloc(rcx)

        dec rdi
        .if rax & rdi

            lea rdx,[rax-sizeof(HEAP)]
            lea rax,[rax+rdi+sizeof(HEAP)]
            not rdi
            and rax,rdi
            lea rcx,[rax-sizeof(HEAP)]
            mov [rcx].HEAP.prev,rdx
            mov [rcx].HEAP.type,_HEAP_ALIGNED

        .endif
    .endif
    ret

_aligned_malloc ENDP

    END
