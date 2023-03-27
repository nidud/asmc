; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
     cursorsize uint_t CURSOR_NORMAL

    .code

    assume rbx:PCURSOR

_getcursor proc uses rbx cursor:PCURSOR

  local ci:CONSOLE_CURSOR_INFO
  local bi:CONSOLE_SCREEN_BUFFER_INFO

    mov rbx,cursor
    .if GetConsoleScreenBufferInfo(_confh, &bi)

        mov [rbx].x,bi.dwCursorPosition.X
        mov [rbx].y,bi.dwCursorPosition.Y
    .endif

    .if GetConsoleCursorInfo(_confh, &ci)

        mov [rbx].csize,ci.dwSize
        mov [rbx].visible,ci.bVisible
    .endif
    ret

_getcursor endp


_setcursor proc uses rbx cursor:PCURSOR

    mov rbx,cursor
    mov edx,[rbx+8]

    SetConsoleCursorPosition(_confh, edx)
    SetConsoleCursorInfo(_confh, rbx)
    ret

_setcursor endp


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


_cursorsize proc size:uint_t

  local ci:CONSOLE_CURSOR_INFO

    mov cursorsize,size
    .if GetConsoleCursorInfo(_confh, &ci)

        mov ci.dwSize,cursorsize
        SetConsoleCursorInfo(_confh, &ci)
    .endif
    ret

_cursorsize endp

    end
