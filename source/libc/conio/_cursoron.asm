; _CURSORON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursoron proc
  local cu:CONSOLE_CURSOR_INFO
    mov cu.dwSize,CURSOR_DEFAULT
    mov cu.bVisible,1
    SetConsoleCursorInfo(_confh, &cu)
    ret
    endp

    end
