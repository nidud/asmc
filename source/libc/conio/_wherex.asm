; _WHEREX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherex proc

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    .if GetConsoleScreenBufferInfo( _confh, &ci )

        movzx eax,ci.dwCursorPosition.x
        movzx edx,ci.dwCursorPosition.y
    .endif
    ret

_wherex endp

    end
