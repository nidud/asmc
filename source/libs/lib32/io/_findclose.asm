; _FINDCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc

    .code

_findclose proc h:HANDLE

    .if !FindClose(h)

        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_findclose endp

    END
