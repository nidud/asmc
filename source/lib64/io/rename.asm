; RENAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

    .code

    option win64:rsp nosave

rename proc Oldname:LPSTR, Newname:LPSTR

    .if MoveFile(rcx, rdx)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

rename endp

    end
