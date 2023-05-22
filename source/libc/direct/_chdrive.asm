; _CHDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc

    .code

_chdrive proc drive:int_t

   .new newdrive[4]:char_t

    ldr eax,drive
    .if ( eax < 1 || eax > 31 )

        _set_doserrno( ERROR_INVALID_DRIVE )
        _set_errno( EACCES )
        .return( -1 )
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
    ret

_chdrive endp

    end
