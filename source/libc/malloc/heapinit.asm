; HEAPINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

.data
 _crtheap HANDLE 0

ifndef __UNIX__
.code

_heap_init proc

    .if ( GetProcessHeap() != NULL )

        mov _crtheap,rax
        mov eax,1
    .endif
    ret

_heap_init endp

.pragma init(_heap_init, 1)
endif

    end
