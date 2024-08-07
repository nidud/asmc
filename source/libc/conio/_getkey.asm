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

ifndef __TTY__
    GetConsoleMode(_coninpfh, &oldstate)
    SetConsoleMode(_coninpfh, 0)
endif

    .for ( :: )

        .ifd ( _readinput( &ConInpRec ) == -1 )

            mov c,eax
           .break
        .endif

        .if ( eax && ConInpRec.EventType == KEY_EVENT && ConInpRec.Event.KeyEvent.bKeyDown )

            movzx   eax,ConInpRec.Event.KeyEvent.wVirtualKeyCode
            shl     eax,8
            mov     al,ConInpRec.Event.KeyEvent.uChar.AsciiChar
ifndef __TTY__
            movzx   edx,al
            cmp     al,ah
            cmovz   eax,edx
endif
            mov     edx,ConInpRec.Event.KeyEvent.dwControlKeyState
            and     edx,LEFT_ALT_PRESSED or SHIFT_PRESSED or LEFT_CTRL_PRESSED
            shl     edx,16
            or      eax,edx
            mov     c,eax
           .break
        .endif
    .endf
ifndef __TTY__
    SetConsoleMode(_coninpfh, oldstate)
endif
    .return( c )

_getkey endp

    end
