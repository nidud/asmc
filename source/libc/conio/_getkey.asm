; _GETKEY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc

define EOF (-1)

    .code

_getkey proc

    .new ConInpRec:INPUT_RECORD
    .new c:int_t = 0
    .new oldstate:DWORD

    ; Switch to raw mode (no line input, no echo input)

    _congetmode( _conin, &oldstate )
    _consetmode( _conin, CONSOLE_INPUT )

    .for ( :: )

        .if ( !_readinput( &ConInpRec ) )

            mov c,EOF
           .break
        .endif

        .if ( ( ConInpRec.EventType == KEY_EVENT ) && ConInpRec.Event.KeyEvent.bKeyDown )

            movzx   eax,ConInpRec.Event.KeyEvent.wVirtualKeyCode
            shl     eax,8
            mov     al,ConInpRec.Event.KeyEvent.uChar.AsciiChar
            mov     edx,ConInpRec.Event.KeyEvent.dwControlKeyState
            and     edx,LEFT_ALT_PRESSED or SHIFT_PRESSED or LEFT_CTRL_PRESSED
            shl     edx,16
            or      eax,edx
            mov     c,eax
           .break
        .endif
    .endf
    _consetmode( _conin, oldstate )
    .return( c )

_getkey endp

    end
