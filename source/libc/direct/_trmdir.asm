; _TRMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif
include tchar.inc

    .code

_trmdir proc directory:tstring_t
ifdef __UNIX__
ifdef _UNICODE
    _set_errno( ENOSYS )
else
    .ifsd ( sys_rmdir( ldr(directory) ) < 0 )

        neg eax
        _set_errno(eax)
    .endif
endif
else
    .if RemoveDirectory( ldr(directory) )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_trmdir endp

    end
