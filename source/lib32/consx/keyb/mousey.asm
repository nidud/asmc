; MOUSEY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

mousey proc

    mov eax,keybmouse_y
    ret

mousey endp

    END
