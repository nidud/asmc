; _MKDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave rsp

_mkdir proc directory:LPSTR

    .if !CreateDirectoryA(rcx, 0)

        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_mkdir endp

    END
