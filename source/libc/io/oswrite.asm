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
   .new hFile:HANDLE = _get_osfhandle( handle )

    .if ( WriteFile( hFile, buffer, size, &NumberOfBytesWritten, 0 ) == 0 )

        _dosmaperr( GetLastError() )
        .return( 0 )
    .endif

    .if ( size != NumberOfBytesWritten )

        _set_errno( ERROR_DISK_FULL )
       .return( 0 )
    .endif
    ret

oswrite endp

    end
