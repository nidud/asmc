; _GETCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

_getcursor proc uses rbx p:PCURSOR
   .new cu:CONSOLE_CURSOR_INFO
   .new ci:CONSOLE_SCREEN_BUFFER_INFO
    ldr rbx,p
    .ifd GetConsoleScreenBufferInfo(_confh, &ci)
        mov [rbx].CURSOR.x,ci.dwCursorPosition.X
        mov [rbx].CURSOR.y,ci.dwCursorPosition.Y
    .endif
    .ifd GetConsoleCursorInfo(_confh, &cu)
        mov [rbx].CURSOR.type,cu.dwSize
        mov [rbx].CURSOR.visible,cu.bVisible
    .endif
    ret
    endp

    end
