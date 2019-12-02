; MOUSEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

mousex proc

    mov eax,keybmouse_x
    ret

mousex endp

    END
