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

_trename proc Oldname:LPTSTR, Newname:LPTSTR

    ldr rcx,Oldname
    ldr rdx,Newname

ifdef __UNIX__

    .if ( !rcx || !rdx )

        _set_errno(EINVAL)
        .return( -1 )
    .endif
    .ifs ( sys_rename(rcx, rdx) < 0 )

        neg eax
        _set_errno(eax)
        .return( -1 )
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
