; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
     cursor CURSOR { -1, -1, CURSOR_DEFAULT, 1 }

    .code

    assume rbx:PCURSOR

_cursoron proc

    .if ( !cursor.visible )

        mov cursor.visible,1
        _cout(ESC "[?25h")
    .endif
    ret

_cursoron endp


_cursoroff proc

    .if ( cursor.visible )

        mov cursor.visible,0
        _cout(ESC "[?25l")
    .endif
    ret

_cursoroff endp


_gotoxy proc x:int_t, y:int_t

    .if ( cursor.x != dil ||
          cursor.y != sil )

        mov cursor.x,dil
        mov cursor.y,sil

        inc edi ; zero based..
        inc esi
        _cout("\e[%d;%dH", esi, edi)
    .endif
    ret

_gotoxy endp


_cursortype proc type:int_t

    .if ( cursor.type != dil )

        mov cursor.type,dil

        _cout(ESC "[%d q", edi)
    .endif
    ret

_cursortype endp

_getcursor proc p:PCURSOR

    mov eax,cursor
    mov [rdi],eax
    ret

_getcursor endp


_setcursor proc uses rbx p:PCURSOR

    mov rbx,rdi
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
