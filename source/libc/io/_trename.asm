; _TRENAME.ASM--
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

_trename proc Oldname:tstring_t, Newname:tstring_t

    ldr rcx,Oldname
    ldr rdx,Newname

ifdef __UNIX__

    .if ( !rcx || !rdx )

        .return( _set_errno( EINVAL ) )
    .endif
    .ifs ( sys_rename(rcx, rdx) < 0 )

        neg eax
        .return( _set_errno( eax ) )
    .endif
    xor eax,eax
else
    .if MoveFile( rcx, rdx )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_trename endp

    end
