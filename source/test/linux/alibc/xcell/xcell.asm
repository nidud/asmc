; _XCELL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
define _CONIO_RETRO_COLORS
include conio.inc

    .code

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }

    mov rcx,_console
    mov rc,[rcx].TCLASS.rc

    _cbeginpaint()
    _scputa(0, 0, rc.col, 0x47)
    mov dil,rc.col
    shr dil,1
    sub dil,12
    _scputs(dil, 0, "Virtual Terminal Sample")

    mov sil,rc.row
    sub sil,10
    mov fc.y,sil
    dec sil
    _scputs(fc.x, sil, "Color Table for Windows Console")
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
    _scputs(fc.x, sil, "Color Table for Terminal")
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
    _scputs(1, rc.row, "./xcell$")
    _cendpaint()
    _gotoxy(9, rc.row)
    ret

paint endp

    assume rbx:THWND

WndProc proc hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uiMsg
    .case WM_CREATE
        _dlshow(hwnd)
        .return( 0 )
    .case WM_CLOSE
        _dlclose(hwnd)
        .return( 0 )
    .endsw
    .return(_defwinproc(hwnd, uiMsg, wParam, lParam))

WndProc endp

main proc

   .new rc:TRECT = { 10, 8, 50, 8 }
   .new c1:TRECT = { 15, 2, 20, 1 }
   .new c2:TRECT = { 15, 3, 20, 1 }
   .new c3:TRECT = { 15, 4, 20, 1 }
   .new dialog:THWND = _dlopen(rc, 3, W_MOVEABLE or W_SHADE, 0)

    mov rbx,rax

    paint()

    _dltitle(rbx, "T_XCELL")
    _rccenter(rc, [rbx].window, c1, _getat(BG_MENU, RED),   "Red")
    _rccenter(rc, [rbx].window, c2, _getat(BG_MENU, GREEN), "Green")
    _rccenter(rc, [rbx].window, c3, _getat(BG_MENU, BLUE),  "Blue")

    _dlinit (rbx, 0, c1, O_DEXIT, T_XCELL, 1, 0)
    _dlinit (rbx, 1, c2, O_DEXIT, T_XCELL, 2, 0)
    _dlinit (rbx, 2, c3, O_DEXIT, T_XCELL, 3, 0)
    _dlmodal(rbx, &WndProc)
    ret

main endp

    end
