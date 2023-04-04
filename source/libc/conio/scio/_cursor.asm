; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
     cursorsize uint_t CURSOR_NORMAL

    .code

_cursoron proc

   .new ci:CONSOLE_CURSOR_INFO = { cursorsize, 1 }

    SetConsoleCursorInfo(_confh, &ci)
    ret

_cursoron endp


_cursoroff proc

   .new ci:CONSOLE_CURSOR_INFO = { cursorsize, 0 }

    SetConsoleCursorInfo(_confh, &ci)
    ret

_cursoroff endp


    assume rcx:PCURSOR

_setcursor proc cursor:PCURSOR

   .new ci:CONSOLE_CURSOR_INFO

ifndef _WIN64
    mov     ecx,cursor
endif
    movzx   eax,[rcx].visible
    mov     ci.bVisible,eax
    mov     al,[rcx].type
    mov     ci.dwSize,eax
    movzx   edx,[rcx].y
    shl     edx,16
    mov     dl,[rcx].x

    SetConsoleCursorPosition(_confh, edx)
    SetConsoleCursorInfo(_confh, &ci)
    ret

_setcursor endp

    assume rbx:PCURSOR

_getcursor proc uses rbx cursor:PCURSOR

   .new ci:CONSOLE_CURSOR_INFO
   .new bi:CONSOLE_SCREEN_BUFFER_INFO

    mov rbx,cursor

    .if GetConsoleScreenBufferInfo(_confh, &bi)

        mov [rbx].x,bi.dwCursorPosition.X
        mov [rbx].y,bi.dwCursorPosition.Y
    .endif

    .if GetConsoleCursorInfo(_confh, &ci)

        mov [rbx].type,ci.dwSize
        mov [rbx].visible,ci.bVisible
    .endif
    ret

_getcursor endp

    end
