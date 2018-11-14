; TINOCANDO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include winbase.inc

    .code

tinocando proc

    .if console & CON_UBEEP

        Beep(9, 1)
    .endif

    mov eax,_TE_CMFAILED ; operation fail (end of line/buffer)
    ret

tinocando endp

    END
