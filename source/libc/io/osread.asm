; OSREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

osread proc handle:int_t, buffer:ptr, size:uint_t
   .new NumberOfBytesRead:DWORD = 0
    mov rcx,_get_osfhandle( ldr(handle) )
    .ifd ( ReadFile( rcx, buffer, size, &NumberOfBytesRead, 0 ) == 0 )
        _dosmaperr( GetLastError() )
        .return( 0 )
    .endif
    .return( NumberOfBytesRead )
    endp

    end
