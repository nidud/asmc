; _RMDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave

_rmdir proc frame directory:LPSTR

    .if RemoveDirectoryA(rcx)
        xor eax,eax
    .else
        _dosmaperr(GetLastError())
    .endif
    ret

_rmdir endp

    END
