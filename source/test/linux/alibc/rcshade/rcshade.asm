; _RCSHADE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc

define AT ((BLUE shl 4) or WHITE)

.code

_getkey proc

   .new cursor_keys[8]:byte = {
        VK_UP,      ; A
        VK_DOWN,    ; B
        VK_RIGHT,   ; C
        VK_LEFT,    ; D
        0,
        VK_END,     ; F
        0,
        VK_HOME     ; H
        }

    .whiled ( _getch() != -1 )

        .if ( eax != VK_ESCAPE )

            .return

        .elseif ( _kbhit() == 0 )

            .return(VK_ESCAPE)
        .endif

        .if ( _getch() == '[' )

            .switch _getch()
            .case 'A'
            .case 'B'
            .case 'C'
            .case 'D'
            .case 'F'
            .case 'H'
                sub eax,'A'
                mov al,cursor_keys[rax]
               .return
            .endsw
        .endif
        _kbflush()
    .endw
    ret

_getkey endp


paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }

    _cbeginpaint()
    mov rcx,_console
    mov rc,[rcx].TCLASS.rc

    _scputa(0, 0, rc.col, 0x47)
    mov dil,rc.col
    shr dil,1
    sub dil,12
    _scputs(dil, 0, "Virtual Terminal Sample")

    mov al,rc.row
    sub al,10
    mov fc.y,al
    mov sil,fc.y
    dec sil
    _scputs(fc.x, sil, " Color Table for Windows Console ")
    _scframe(fc, BOX_SINGLE_ARC, 0)

    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        mov sil,fc.y
        inc sil
        movzx eax,bh
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, sil, 2, eax)
    .endf

    add fc.y,5
    mov sil,fc.y
    dec sil
    _scputs(fc.x, sil, " Color Table for Terminal ")
    _scframe(fc, BOX_SINGLE_ARC, 0)
    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        mov sil,fc.y
        inc sil
        movzx eax,bh
        lea rdx,_terminalcolorid
        mov al,[rdx+rax]
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, sil, 2, eax)
    .endf
    dec rc.row
    _scputs(1, rc.row, "./rcshade$")
    _cendpaint()
    _gotoxy(12, rc.row)
    ret

paint endp


main proc

   .new rc:TRECT = { 10, 5, 60, 14 }
   .new b1:TRECT = {  0, 0, 60, 14 }
   .new p:PCHAR_INFO = _rcalloc(rc, 1)

    paint()

    _rcclear(rc, p, (AT shl 16) or ' ')
    _rcframe(rc, b1, p, BOX_SINGLE_ARC, 0)
    _rcputs(rc, p, 2, 2, 0, "Use Left, Right, Up, or Down to Move")
    _rcxchg(rc, p)
    _rcshade(rc, p, 1)

    .while 1
        .switch _getkey()
        .case 0x0A
        .case VK_ESCAPE
            .break
        .case VK_LEFT
            _rcshade(rc, p, 0)
            mov rc,_rcmovel(rc, p)
            _rcshade(rc, p, 1)
           .endc
        .case VK_RIGHT
            _rcshade(rc, p, 0)
            mov rc,_rcmover(rc, p)
            _rcshade(rc, p, 1)
           .endc
        .case VK_UP
            _rcshade(rc, p, 0)
            mov rc,_rcmoveu(rc, p)
            _rcshade(rc, p, 1)
           .endc
        .case VK_DOWN
            _rcshade(rc, p, 0)
            mov rc,_rcmoved(rc, p)
            _rcshade(rc, p, 1)
        .endsw
    .endw
    _rcxchg(rc, p)
    .return(0)
main endp

    end
