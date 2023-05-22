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
    .if ( [rbx].visible )

        _cursoron()
    .else
        _cursoroff()
    .endif
    _cursortype( [rbx].type )
    ret

_setcursor endp

    end
