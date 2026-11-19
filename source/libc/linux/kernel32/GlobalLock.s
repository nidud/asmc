; GLOBALLOCK.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalLock proc WINAPI hMem:HGLOBAL
    ldr rax,hMem
    .if ( !rax )
        SetLastError( ERROR_INVALID_HANDLE )
       .return( NULL )
    .endif
    inc [rax-HEAP].HEAP.type ; LockCount
    ret
    endp

    end
