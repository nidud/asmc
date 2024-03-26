; _CHDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

_chdrive proc drive:int_t
ifdef __UNIX__
    _set_errno( ENOSYS )
else
   .new newdrive[4]:char_t

    ldr eax,drive
    .if ( eax < 1 || eax > 31 )

        _set_doserrno( ERROR_INVALID_DRIVE )
        .return( _set_errno( EACCES ) )
    .endif

    add al,'A' - 1
    mov newdrive[0],al
    mov newdrive[1],':'
    mov newdrive[2],0

    .if SetCurrentDirectory( &newdrive )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_chdrive endp

    end
