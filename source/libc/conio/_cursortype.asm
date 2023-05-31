; _CURSORTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursortype proc type:int_t

ifdef __TTY__
    ldr edx,type

    .if ( _cursor.type != dl )

        mov _cursor.type,dl
        _cout(ESC "[%d q", edx)
    .endif
else
  local cu:CONSOLE_CURSOR_INFO

    .if GetConsoleCursorInfo(_confh, &cu)

        mov cu.dwSize,type
        SetConsoleCursorInfo(_confh, &cu)
    .endif
endif
    ret

_cursortype endp

    end
