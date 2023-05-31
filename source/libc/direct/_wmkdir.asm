; _WMKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

_wmkdir proc directory:LPWSTR

    ldr rcx,directory
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
else
    .if CreateDirectoryW( rcx, 0 )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_wmkdir endp

    end
