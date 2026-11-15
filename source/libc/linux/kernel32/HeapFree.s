; HEAPFREE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/mman.inc
include heapapi.inc

.code

 HeapFree proc WINAPI uses rsi rdi rbx hHeap:HANDLE, dwFlags:DWORD, lpMem:ptr
    ldr rbx,lpMem
    .if ( !rbx )
        .return( TRUE )
    .endif
    sub rbx,16
    .ifsd ( munmap(rbx, [rbx]) < 0 )
        .return( FALSE )
    .endif
    .return( TRUE )
    endp

    end
