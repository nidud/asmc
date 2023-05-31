; _CURSORON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursoron proc

ifdef __TTY__
    mov _cursor.visible,1
    _cout(ESC "[?25h")
else
  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    SetConsoleCursorInfo(_confh, &cu)
endif
    ret

_cursoron endp

    end
