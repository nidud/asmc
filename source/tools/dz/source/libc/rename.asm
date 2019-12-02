; RENAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

externdef _diskflag:DWORD

.code

rename proc Oldname:LPSTR, Newname:LPSTR

    .if MoveFileA(Oldname, Newname)

        xor eax,eax
        mov _diskflag,1

    .else
        osmaperr()
    .endif
    ret

rename endp

    end
