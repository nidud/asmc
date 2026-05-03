; MESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)

.code

_tmain proc argc:int_t, argv:array_t

   .new msg:MESSAGE
   .new Escape:int_t = 2
   .new rc:TRECT = { 10, 4, 40, 18 }
   .new sc:TRECT
   .new p:PCHAR_INFO = _rcalloc(rc, 0)
   .new x:byte, y:byte

    mov rdi,rax
    mov eax,rc
    shr eax,16
    mov edx,eax
    shl edx,16
    mov sc,edx
    mul ah
    mov ecx,eax
    mov eax,(AT shl 16) or ' '
    rep stosd
    _rcframe(rc, sc, p, BOX_SINGLE_ARC, 0)
    _rcxchg(rc, p)

    mov sc,rc
    add sc.x,2
    add sc.y,sc.row
    sub sc.y,3

    _scputs(sc.x,  5, "_getmessage(MESSAGE, NULL)")

    _scputs(sc.x,  7, "WM_KEYDOWN")
    _scputs(sc.x,  8, ".lParam")
    _scputs(sc.x,  9, ".wParam")

    _scputs(sc.x, 11, "WM_KEYUP")
    _scputs(sc.x, 12, ".lParam")
    _scputs(sc.x, 13, ".wParam")

    _scputs(sc.x, 15, ".message")
    _scputs(sc.x, 16, ".lParam")
    _scputs(sc.x, 17, ".wParam")

    _scputs(sc.x, sc.y, "Hit Escape two times to Quit")

    mov x,sc.x
    add x,14

    .while 1

        _getmessage(&msg, NULL, 1)

        .break .if ( eax == -1 )

        _dispatchmsg(&msg)

        .switch msg.message
        .case WM_KEYDOWN
            mov y,7
            .if ( msg.wParam == VK_ESCAPE )
                _scputfg(sc.x, sc.y, 28, 11)
                dec Escape
               .break .ifz
            .else
                _scputfg(sc.x, sc.y, 28, AT)
                mov Escape,2
            .endif
           .endc
        .case WM_KEYUP
            mov y,11
           .endc
        .default
            mov y,15
           .endc
        .endsw

        _scputf( x, y, "%08X", msg.message )
        inc y
        _scputf( x, y, "%08X", msg.lParam  )
        inc y
        _scputf( x, y, "%08X", msg.wParam  )
    .endw
    _rcxchg(rc, p)
    .return( 0 )

_tmain endp

    end _tstart

