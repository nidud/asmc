; _TRMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif
include tchar.inc

    .code

_trmdir proc directory:LPTSTR
    ldr rcx,directory
ifdef __UNIX__
ifdef _UNICODE
    _set_errno( ENOSYS )
    mov eax,-1
else
    .ifsd ( sys_rmdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
        mov rax,-1
    .endif
endif
else
    .if RemoveDirectory( rcx )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_trmdir endp

    end
