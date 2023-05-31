; OSWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

.code

oswrite proc uses rbx handle:int_t, buffer:ptr, size:uint_t
ifdef __UNIX__

    ldr ecx,handle
    ldr rax,buffer
    ldr ebx,size

    .ifs ( sys_write(ecx, rax, rbx) < 0 )

        neg eax
        _set_errno( eax )
        xor eax,eax
    .endif

    .if ( rax != rbx )

        _set_errno( ENOSPC )
       .return( 0 )
    .endif

else

   .new NumberOfBytesWritten:uint_t = 0
   .new hFile:HANDLE = _get_osfhandle( handle )

    .if ( WriteFile( hFile, buffer, size, &NumberOfBytesWritten, 0 ) == 0 )

        _dosmaperr( GetLastError() )
        .return( 0 )
    .endif

    .if ( size != NumberOfBytesWritten )

        _dosmaperr( ERROR_DISK_FULL )
       .return( 0 )
    .endif
endif
    ret

oswrite endp

    end
