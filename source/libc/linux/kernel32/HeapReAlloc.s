; HEAPREALLOC.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include heapapi.inc

.code

 HeapReAlloc proc WINAPI uses rsi rdi rbx hHeap:HANDLE, dwFlags:DWORD, lpMem:ptr, dwBytes:size_t
   .new old_size:size_t
    ldr rbx,lpMem
    .if ( !rbx )
        .return HeapAlloc(ldr(hHeap), ldr(dwFlags), ldr(dwBytes))
    .endif
    mov rax,[rbx-8]
    mov old_size,rax
    mov rdi,HeapAlloc(ldr(hHeap), ldr(dwFlags), ldr(dwBytes))
    .if ( !rdi )
        .return( NULL )
    .endif
    mov rcx,old_size
    mov rdx,dwBytes
    .if ( rcx > rdx )
        mov rcx,rdx
    .endif
    mov rsi,rbx
    rep movsb
    mov rcx,rbx
    mov rbx,rax
    HeapFree(hHeap, 0, rcx)
    .return( rbx )
    endp

    end
