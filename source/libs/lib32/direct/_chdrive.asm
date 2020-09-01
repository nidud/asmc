; _CHDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc

    .code

_chdrive proc drive:SINT

    mov eax,drive
    .ifs eax > 0 || eax > 31

        add al,'A' - 1
        mov ah,':'
        mov drive,eax

        .if SetCurrentDirectory(&drive)

            xor eax,eax
        .else
            osmaperr()
        .endif
    .else
        mov errno,EACCES
        mov _doserrno,ERROR_INVALID_DRIVE
        or  eax,-1
    .endif
    ret

_chdrive endp

    END
