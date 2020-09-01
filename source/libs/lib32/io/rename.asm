; RENAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

.code

rename proc Oldname:LPSTR, Newname:LPSTR

    .if MoveFileA(Oldname, Newname)

        xor eax,eax

    .else
        osmaperr()
    .endif
    ret

rename endp

    end
