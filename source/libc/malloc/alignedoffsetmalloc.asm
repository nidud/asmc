; ALIGNEDOFFSETMALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void * _aligned_offset_malloc(size_t size, size_t alignment, size_t offset);
;
include malloc.inc
include errno.inc

.code

_aligned_offset_malloc proc uses rbx size:size_t, alignment:size_t, offs:size_t

    ldr rbx,alignment
    ldr rcx,size
    ldr rdx,offs

    lea rax,[rbx-1]
    .if ( !rbx || rbx & rax || ( rdx && rdx >= rcx ) )

        _set_errno(EINVAL)
        .return( NULL )
    .endif

    .if ( ebx < HEAP )
        mov eax,HEAP-1
    .endif
    mov rbx,rax

    neg rdx
    and edx,HEAP-1
    lea rax,[rax+rdx+HEAP]
    mov size,rax
    add rax,rcx
    .if ( rcx > rax )

        _set_errno(ENOMEM)
        .return( NULL )
    .endif
    .if ( malloc(rax) == NULL )
        .return
    .endif
    lea rcx,[rax-HEAP]
    add rax,size
    add rax,offs
    not rbx
    and rax,rbx
    sub rax,offs
    mov [rax-HEAP].HEAP.type,_HEAP_ALIGNED
    mov [rax-HEAP].HEAP.prev,rcx
    ret

_aligned_offset_malloc endp

    end
