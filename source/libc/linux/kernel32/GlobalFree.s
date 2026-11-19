; GLOBALFREE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalFree proc WINAPI hMem:HGLOBAL
    ldr rcx,hMem
    .if ( rcx )
        sub rcx,HEAP
        free( rcx )
    .endif
    .return( NULL )
    endp

    end
