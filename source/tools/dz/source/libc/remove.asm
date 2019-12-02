; REMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

externdef _diskflag:DWORD

.code

remove proc file:LPSTR

    .if DeleteFileA(file)

        xor eax,eax
        mov _diskflag,1
    .else
        osmaperr()
    .endif
    ret

remove endp

    end
