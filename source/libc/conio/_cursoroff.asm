; _CURSOROFF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursoroff proc
ifdef __TTY__
    mov _cursor.visible,0
    _cout(ESC "[?25l")
else
  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,0
    SetConsoleCursorInfo(_confh, &cu)
endif
    ret

_cursoroff endp

    end
