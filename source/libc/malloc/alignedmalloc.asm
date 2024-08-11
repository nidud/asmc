; ALIGNEDMALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

_aligned_malloc proc uses rbx dwSize:size_t, Alignment:size_t

    ldr rbx,Alignment
    ldr rcx,dwSize
    lea rcx,[rcx+rbx+HEAP]

    .if malloc( rcx )

        dec rbx
        .if ( rax & rbx )

            lea rdx,[rax-HEAP]
            lea rax,[rax+rbx+HEAP]
            not rbx
            and rax,rbx
            lea rcx,[rax-HEAP]
            mov [rcx].HEAP.prev,rdx
            mov [rcx].HEAP.type,_HEAP_ALIGNED
        .endif
    .endif
    ret

_aligned_malloc endp

    end
