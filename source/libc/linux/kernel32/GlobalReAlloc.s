; GLOBALREALLOC.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalReAlloc proc WINAPI uses rsi rdi rbx hMem:HGLOBAL, dwBytes:SIZE_T, uFlags:UINT
   .new oldSize:size_t
   .new oldFlags:UINT
   .new oldLock:UINT
   .new total:size_t
    ldr rcx,hMem
    .if ( !rcx )
        .return( GlobalAlloc( ldr(uFlags), ldr(dwBytes) ) )
    .endif
    ldr rbx,dwBytes
    sub rcx,HEAP
    mov rax,[rcx].HEAP.size
    mov oldSize,rax
    mov rax,[rcx].HEAP.prev
    mov oldFlags,eax
    movzx eax,[rcx].HEAP.type ; LockCount
    mov oldLock,eax
    mov rax,rbx
    add rax,HEAP
    .if ( rax < rbx )
        .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
    .endif
    mov total,rax
    realloc(rcx, rax)
    .if ( !rax )
        .return( SetLastError( ERROR_NOT_ENOUGH_MEMORY ) )
    .endif
    mov rsi,rax
    mov [rsi].HEAP.size,rbx
    mov eax,oldLock
    mov [rsi].HEAP.type,al
    .if ( uFlags & GMEM_ZEROINIT )
        mov rcx,rbx
        .if ( rcx > oldSize )
            sub rcx,oldSize
            lea rdi,[rsi+HEAP]
            add rdi,oldSize
            xor eax,eax
            rep stosb
        .endif
    .endif
    lea rax,[rsi+HEAP]
    ret
    endp

    end
