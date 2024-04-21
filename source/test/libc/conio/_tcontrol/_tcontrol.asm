; _TCONTROL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; A text control is added externally (Unicode/ASCII) and buffering
; added to the main window (128*TCHAR+TEDIT)
;
; Flags:
;
; O_DEXIT   - dialog exits on Enter
; O_USEBEEP - if no-can-do: try to delete a char at the end
; O_SELECT  - text is auto selected on entry
;
define _CONIO_RETRO_COLORS
include conio.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)

.code

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }
   .new y:byte

    _cbeginpaint()
    mov rcx,_console
    mov rc,[rcx].TCLASS.rc

    _scputa(0, 0, rc.col, 0x47)
    mov cl,rc.col
    shr cl,1
    sub cl,12
    _scputs(cl, 0, "Virtual Terminal Sample")

    _scputs(2, 2, "A text control is added externally (Unicode/ASCII) and buffering")
    _scputs(2, 3, "added to the main window (128*TCHAR+TEDIT)")

    _scputs(2, 5, "Flags:")

    _scputs(2, 7, "O_DEXIT   - dialog exits on Enter")
    _scputs(2, 8, "O_USEBEEP - if no-can-do: try to delete a char at the end")
    _scputs(2, 9, "O_SELECT  - text is auto selected on entry")


    mov al,rc.row
    sub al,10
    mov fc.y,al
    mov cl,fc.y
    dec cl
    _scputs(fc.x, cl, " Color Table for Windows Console ")
    _scframe(fc, BOX_SINGLE_ARC, 0)

    mov al,fc.y
    inc al
    mov y,al

    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        movzx eax,bh
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, y, 2, eax)
    .endf

    add fc.y,5
    mov cl,fc.y
    dec cl
    _scputs(fc.x, cl, " Color Table for Terminal ")
    _scframe(fc, BOX_SINGLE_ARC, 0)
    .for ( ebx = 4 : bh < 16 : bh++, bl+=3 )

        mov al,fc.y
        inc al
        mov y,al
        movzx eax,bh
        lea rdx,_terminalcolorid
        mov al,[rdx+rax]
        shl eax,16
        mov ax,U_FULL_BLOCK
        _scputw(bl, y, 2, eax)
    .endf
    dec rc.row
    _scputs(1, rc.row, "./_tcontrol$")
    _cendpaint()
    _gotoxy(14, rc.row)
    ret

paint endp

    assume rbx:THWND

WndProc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov rbx,hwnd
    .switch uiMsg
    .case WM_CREATE
        _dlshow(rbx)
        _tcontrol([rbx].object, 128, ' ', "string to edit...")
        .return( 0 )
    .case WM_CLOSE
        _dlclose(rbx)
        .return( 0 )
    .default
        mov rbx,[rbx].object
        .if ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .return
        .endif
    .endsw
    .return(_defwinproc(hwnd, uiMsg, wParam, lParam))

WndProc endp

_tmain proc

   .new rc:TRECT = { 10, 8, 50, 8 }
   .new f1:TRECT = { 16, 0, 18, 3 }
   .new f2:TRECT = { 14, 4, 22, 3 }
   .new ec:TRECT = { 15, 5, 20, 1 }

    paint()

    mov rbx,_dlopen(rc, 1, W_UTF16 or W_MOVEABLE or W_TRANSPARENT or W_SHADE, 128*TCHAR+TEDIT)
    _rcframe(rc, f1, [rbx].window, BOX_SINGLE_ARC, 0x0F)
    _rcframe(rc, f2, [rbx].window, BOX_SINGLE_ARC, 0x06)
    _rcputs(rc, [rbx].window, 17, 1, 0x0F, "  Text Control  ")

    assume rcx:THWND

    mov     rcx,[rbx].object
    mov     [rcx].rc,ec
    mov     [rcx].type,T_EDIT
    or      [rcx].flags,W_WNDPROC or O_DEXIT or O_USEBEEP or O_SELECT
    movzx   eax,[rbx].rc.col
    mul     [rcx].rc.y
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].window
    mov     [rcx].window,rax
    mov     [rcx].index,0

    _dlinit(rcx, 0)
    _dlmodal(rbx, &WndProc)
    xor eax,eax
    ret

_tmain endp

    end
