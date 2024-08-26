; MSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; size_t _msize(void *memblock);
;
include malloc.inc
include errno.inc

.code

_msize proc memblock:ptr

    ldr rcx,memblock

    .if ( rcx == NULL )

        _set_errno(EINVAL)
    .else

        lea rdx,[rcx-HEAP]
        .if ( [rdx].HEAP.type == _HEAP_ALIGNED )
            mov rdx,[rdx].HEAP.prev
        .endif
        mov rax,[rdx].HEAP.size
        sub rcx,rdx
        sub rax,rcx
    .endif
    ret

_msize endp

    end
