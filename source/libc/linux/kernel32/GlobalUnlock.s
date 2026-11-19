; GLOBALUNLOCK.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalUnlock proc WINAPI hMem:HGLOBAL
    ldr rax,hMem
    .if ( !rax )
        SetLastError( ERROR_INVALID_HANDLE )
       .return( FALSE )
    .endif
    .if ( [rax-HEAP].HEAP.type == 0 )
        SetLastError( ERROR_NOT_LOCKED )
       .return( FALSE )
    .endif
    dec [rax-HEAP].HEAP.type ; LockCount
    .ifz
        SetLastError( NO_ERROR )
       .return( FALSE )
    .endif
    .return( TRUE )
    endp

    end
