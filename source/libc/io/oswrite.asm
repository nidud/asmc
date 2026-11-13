; OSWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

oswrite proc handle:int_t, buffer:ptr, size:uint_t
    .new NumberOfBytesWritten:uint_t = 0
    .new hFile:HANDLE = _get_osfhandle( ldr(handle) )
    .if ( WriteFile( hFile, buffer, size, &NumberOfBytesWritten, 0 ) == 0 )
        _dosmaperr( GetLastError() )
        xor eax,eax
    .elseif ( size != NumberOfBytesWritten )
        _dosmaperr( ERROR_DISK_FULL )
        xor eax,eax
    .endif
    ret
    endp

    end
