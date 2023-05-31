; _RMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

    .code

_rmdir proc directory:LPSTR

    ldr rcx,directory
ifdef __UNIX__
    .ifsd ( sys_rmdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
else
    .if RemoveDirectoryA( rcx )
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_rmdir endp

    end
