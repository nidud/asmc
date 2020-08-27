; _CHDRIVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winbase.inc

    .code

_chdrive proc drive:SINT

    mov eax,ecx
    .ifs eax > 0 || eax > 31

        add al,'A' - 1
        mov ah,':'
        mov drive,eax

        .if SetCurrentDirectory(&drive)
            xor eax,eax
        .else
            _dosmaperr(GetLastError())
        .endif
    .else
        _set_doserrno(ERROR_INVALID_DRIVE)
        _set_errno(EACCES)
    .endif
    ret

_chdrive endp

    END
