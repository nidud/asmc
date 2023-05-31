; _GETCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_getcursor proc uses rbx p:PCURSOR

    ldr rbx,p
ifdef __TTY__
    mov [rbx].CURSOR.type,_cursor.type
    mov [rbx].CURSOR.visible,_cursor.visible
    _cursorxy()
    movzx ecx,ax
    shr eax,16
    mov _cursor.x,cl
    mov _cursor.y,al
    mov [rbx].CURSOR.x,cl
    mov [rbx].CURSOR.y,al
else
   .new cu:CONSOLE_CURSOR_INFO
   .new ci:CONSOLE_SCREEN_BUFFER_INFO

    .if GetConsoleScreenBufferInfo(_confh, &ci)

        mov [rbx].CURSOR.x,ci.dwCursorPosition.X
        mov [rbx].CURSOR.y,ci.dwCursorPosition.Y
    .endif
    .if GetConsoleCursorInfo(_confh, &cu)

        mov [rbx].CURSOR.type,cu.dwSize
        mov [rbx].CURSOR.visible,cu.bVisible
    .endif
endif
    ret

_getcursor endp

    end
