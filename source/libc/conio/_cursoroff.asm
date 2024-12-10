; _CURSOROFF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursoroff proc

  local cu:CONSOLE_CURSOR_INFO

ifdef __TTY__
    mov rcx,_console
    mov cu.dwSize,[rcx].TCONSOLE.csize
else
    mov cu.dwSize,CURSOR_DEFAULT
endif
    mov cu.bVisible,0
    _setconsolecursorinfo(_confh, &cu)
    ret

_cursoroff endp

    end
