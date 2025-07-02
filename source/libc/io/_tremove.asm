; _TREMOVE.ASM--
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
include tchar.inc

.code

_tremove proc file:tstring_t

    ldr rcx,file

ifdef __UNIX__

    .if ( !rcx )

        .return( _set_errno( EINVAL ) )
    .endif

    .ifs ( sys_unlink(rcx) < 0 )

        neg eax
        .return( _set_errno(eax) )
    .endif
    xor eax,eax
else
    .if DeleteFile( rcx )

        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tremove endp

    end
