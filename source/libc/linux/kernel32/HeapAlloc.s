; HEAPALLOC.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/mman.inc
include heapapi.inc

define PAGE_SIZE 4096

.code

 HeapAlloc proc WINAPI uses rsi rdi rbx hHeap:HANDLE, dwFlags:DWORD, dwBytes:size_t
    ldr rsi,dwBytes
    mov rbx,rsi
    lea rsi,[rsi+16+PAGE_SIZE-1]
    and rsi,-PAGE_SIZE
    .if ( mmap(NULL, rsi, PROT_READ or PROT_WRITE, MAP_PRIVATE or MAP_ANONYMOUS, -1, 0) == MAP_FAILED )
        .return( NULL )
    .endif
    mov [rax+8],rbx  ; requested byte size (for HeapSize / HeapReAlloc)
    lea rbx,[rbx+16+PAGE_SIZE-1]
    and rbx,-PAGE_SIZE
    mov [rax],rbx    ; total mapped byte length (for munmap)
    add rax,16
    ret
    endp

    end
