; _WRENAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

    .code

_wrename proc Oldname:LPWSTR, Newname:LPWSTR

    .if MoveFileW(Oldname, Newname)

        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_wrename endp

    end
