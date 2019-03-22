; _MKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc
include errno.inc

    .code

    option win64:nosave

_mkdir proc frame directory:LPSTR

    .if !CreateDirectoryA(rcx, 0)

        _dosmaperr(GetLastError())
    .else
        xor eax,eax
    .endif
    ret

_mkdir endp

    END
