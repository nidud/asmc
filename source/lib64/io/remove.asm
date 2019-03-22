; REMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

remove proc frame file:LPSTR

    .if DeleteFileA(rcx)

        xor eax,eax
    .else
        _dosmaperr(GetLastError())
    .endif
    ret

remove endp

    END
