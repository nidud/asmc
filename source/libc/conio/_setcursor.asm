; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PCURSOR

_setcursor proc uses rbx p:PCURSOR

    ldr rbx,p

    _gotoxy([rbx].x, [rbx].y)
ifdef __TTY__
    .if ( [rbx].visible )
        _cursoron()
    .else
        _cursoroff()
    .endif
    _cursortype( [rbx].type )
else
   .new cu:CONSOLE_CURSOR_INFO

    movzx eax,[rbx].type
    movzx ecx,[rbx].visible
    mov cu.dwSize,eax
    mov cu.bVisible,ecx
    SetConsoleCursorInfo(_confh, &cu)
endif
    ret

_setcursor endp

    end
