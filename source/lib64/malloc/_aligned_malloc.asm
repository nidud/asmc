; _ALIGNED_MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

    option win64:2

_aligned_malloc proc uses rdi dwSize:size_t, Alignment:size_t

    mov rdi,rdx
    lea rcx,[rcx+rdx+sizeof(S_HEAP)]

    .if malloc(rcx)

        dec rdi
        .if rax & rdi

            lea rdx,[rax-sizeof(S_HEAP)]
            lea rax,[rax+rdi+sizeof(S_HEAP)]
            not rdi
            and rax,rdi
            lea rcx,[rax-sizeof(S_HEAP)]
            mov [rcx].S_HEAP.h_prev,rdx
            mov [rcx].S_HEAP.h_type,_HEAP_ALIGNED

        .endif
    .endif
    ret

_aligned_malloc ENDP

    END
