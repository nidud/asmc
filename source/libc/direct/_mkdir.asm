; _MKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif

    .code

_mkdir proc directory:LPSTR

    ldr rcx,directory

ifdef __UNIX__
    .ifsd ( sys_mkdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
else
    .ifd !CreateDirectoryA( rcx, 0 )

        _dosmaperr( GetLastError() )
    .else
        xor eax,eax
    .endif
endif
    ret

_mkdir endp

    end
