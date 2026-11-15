; HEAPSIZE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include heapapi.inc

.code

 HeapSize proc WINAPI hHeap:HANDLE, dwFlags:DWORD, lpMem:ptr
    ldr rcx,lpMem
    .if ( !rcx )
        .return( -1 )
    .endif
    mov rax,[rcx-8] ; requested byte size
    ret
    endp

    end
