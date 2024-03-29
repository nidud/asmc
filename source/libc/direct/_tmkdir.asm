; _WMKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif
include tchar.inc

    .code

_tmkdir proc directory:LPTSTR

    ldr rcx,directory
ifdef __UNIX__
ifdef _UNICODE
    _set_errno( ENOSYS )
else
    .ifsd ( sys_mkdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
    .endif
endif
else
    .if CreateDirectory( rcx, 0 )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tmkdir endp

    end
