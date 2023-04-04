; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .data
     cursor CURSOR { 0, 0, CURSOR_DEFAULT, 1 }

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


_cursorxy proc uses rbx r12 xp:ptr int_t, yp:ptr int_t

    mov rbx,xp
    mov r12,yp

    _cout("\e[6n")
    _getcsi2(rbx, r12)
    ret

_cursorxy endp


_gotoxy proc _x:int_t, _y:int_t

    mov eax,_x
    mov edx,_y

    .if ( cursor.x != al ||
          cursor.y != dl )

        mov cursor.x,al
        mov cursor.y,dl

        inc eax ; zero based..
        inc edx
        _cout("\e[%d;%dH", eax, edx)
    .endif
    ret

_gotoxy endp

_cursortype proc _type:int_t

    mov eax,_type
    .if ( cursor.type != al )

        mov cursor.type,al

        _cout(ESC "[%d q", eax)
    .endif
    ret

_cursortype endp

_getcursor proc p:PCURSOR

    mov eax,cursor
    mov [rdi],eax
    ret

_getcursor endp


_setcursor proc uses rbx p:PCURSOR

    mov rbx,p
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
