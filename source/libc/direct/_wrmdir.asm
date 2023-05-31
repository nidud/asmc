; _WRMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

_wrmdir proc directory:LPWSTR
    ldr rcx,directory
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
else
    .if RemoveDirectoryW( rcx )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_wrmdir endp

    end
