; GETSCREENRECT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

GetScreenRect proc

    mov eax,_scrcol
    mov ah,byte ptr _scrrow
    shl eax,16
    ret

GetScreenRect endp

    END
