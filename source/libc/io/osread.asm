; OSREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif

    .code

osread proc handle:int_t, buffer:ptr, size:uint_t
ifdef __UNIX__

    .ifsd ( sys_read( ldr(handle), ldr(buffer), ldr(size) ) < 0 )

        neg eax
        _set_errno( eax )
        xor eax,eax
    .endif

else
    .new NumberOfBytesRead:DWORD = 0
    .new hFile:HANDLE = _get_osfhandle( handle )

    .ifd ( ReadFile( hFile, buffer, size, &NumberOfBytesRead, 0 ) == 0 )

        _dosmaperr( GetLastError() )
        .return( 0 )
    .endif
    .return( NumberOfBytesRead )
endif

osread endp

    end
