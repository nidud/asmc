; GLOBALALLOC.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalAlloc proc WINAPI uses rbx uFlags:UINT, dwBytes:SIZE_T
    ldr ecx,uFlags
    ldr rdx,dwBytes
    mov rbx,rdx
    add rdx,HEAP
    .if ( rdx < rbx )
        SetLastError( ERROR_NOT_ENOUGH_MEMORY )
       .return( NULL )
    .endif
    .if ( ecx & GMEM_ZEROINIT )
        calloc( 1, rdx )
    .else
        malloc( rdx )
    .endif
    .if ( !rax )
        SetLastError( ERROR_NOT_ENOUGH_MEMORY )
       .return( NULL )
    .endif
    mov [rax].HEAP.size,rbx
    mov ecx,uFlags
    mov [rax].HEAP.prev,rcx ; Flags
    mov [rax].HEAP.type,0   ; LockCount
    add rax,HEAP
    ret
    endp

    end
