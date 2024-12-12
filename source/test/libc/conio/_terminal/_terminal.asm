; TERMINAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc
include tchar.inc

.code

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }

    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc

    _cbeginpaint()
    _scputa(0, 0, rc.col, 0x47)
    mov al,rc.col
    shr al,1
    sub al,12
    _scputs(al, 0, "Virtual Terminal Sample")

    mov al,rc.row
    sub al,9
    mov fc.y,al
    dec al
    _scputs(fc.x, al, "Color Table for Windows Console")
    _scframe(fc, BOX_SINGLE_ARC, 0)

    inc fc.y
    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        movzx eax,bh
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, fc.y, 2, eax)
    .endf

    add fc.y,3
    mov cl,fc.y
    dec cl
    _scputs(fc.x, cl, "Color Table for Terminal")
    _scframe(fc, BOX_SINGLE_ARC, 0)
    inc fc.y
    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        movzx eax,bh
        lea rdx,_terminalcolorid
        mov al,[rdx+rax]
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, fc.y, 2, eax)
    .endf
    dec rc.row
    _scputs(1, rc.row, "./terminal$")
    _cendpaint()
    _gotoxy(13, rc.row)
    ret

paint endp


_tmain proc

   .new y:byte = 0
   .new a:AnsiEscapeCode = {0}
   .new s:ptr = _conpush()

    paint()

    _write(_confd, CSI "c", 3) ; read terminal identity
    _readansi(&a)
    .if ( a.param == '?' && a.n[4] != 0 )
        mov y,5
    .endif
    mov eax,a.n
    .while ( eax < 100 )
        imul eax,eax,10
    .endw
    _scputf(2, 2, "Terminal type: VT%03d", eax)
    _scputs(3, 4, "Supported features:")

    .if ( y )

        .for ( ebx = 1 : bl < a.count : ebx++, y++ )

            mov eax,a.n[rbx*4]
            .switch pascal eax
            .case  1: _scputs(4, y, "132-columns")
            .case  2: _scputs(4, y, "Printer")
            .case  3: _scputs(4, y, "ReGIS graphics")
            .case  4: _scputs(4, y, "Sixel graphics")
            .case  6: _scputs(4, y, "Selective erase")
            .case  8: _scputs(4, y, "User-defined keys")
            .case  9: _scputs(4, y, "National Replacement Character sets.")
            .case 15: _scputs(4, y, "Technical characters")
            .case 18: _scputs(4, y, "User windows")
            .case 21: _scputs(4, y, "Horizontal scrolling")
            .case 22: _scputs(4, y, "ANSI color, e.g., VT525")
            .case 29: _scputs(4, y, "ANSI text locator (i.e., DEC Locator mode)")
            .default
            .break
            .endsw
        .endf
    .endif

    mov rcx,_console
    mov al,[rcx].TCONSOLE.rc.row
    dec al
    mov y,al

    _write(_confd, SET_ANY_EVENT_MOUSE, 8)
    .whiled ( _readansi( &a ) )

        .break .if ( a.final == VK_ESCAPE || a.final == VK_RETURN )
        _scputf(13, y, "%c %d %d %d %3d %3d %3d %3d",
            a.final, a.count, a.param, a.inter, a.n[0x0], a.n[0x4], a.n[0x8], a.n[0xC])
    .endw
    _write(_confd, RST_ANY_EVENT_MOUSE, 8)
    _conpop(s)
    .return(0)

_tmain endp

    end
