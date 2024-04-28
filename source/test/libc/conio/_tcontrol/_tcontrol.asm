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
include string.inc
include tchar.inc

define AT ((BLUE shl 4) or WHITE)

.code

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }
   .new y:byte

    _cbeginpaint()
    mov rcx,_console
    mov rc,[rcx].TCONSOLE.rc

    _scputa(0, 0, rc.col, 0x47)
    mov cl,rc.col
    shr cl,1
    sub cl,12
    _scputs(cl, 0, "Virtual Terminal Sample")

    _scputs(2, 2, "A text control is added to _console")
    _scputs(2, 5, "Flags:")
    _scputs(2, 7, "O_DEXIT       - Exit on VK_RETURN")
    _scputs(2, 8, "O_USEBEEP     - If NoCanDo: delete a char at the end")
    _scputs(2, 9, "O_AUTOSELECT  - Auto select text on activation")
    _scputs(2,10, "O_MYBUF       - Local buffer")

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
    _gotoxy(14, rc.row)

    sub fc.y,10
    mov cl,fc.y
    dec cl
    _scputs(fc.x, cl, " Text Control ")

    _scframe(fc, BOX_SINGLE_ARC, 0x06)
    _cendpaint()
    mov eax,fc
    ret

paint endp

WndProc proc private hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr eax,uiMsg
    .if ( eax == WM_CREATE || eax == WM_CLOSE )

        .return( 0 )
    .endif
ifdef _WIN64
    _defwinproc()
else
    _defwinproc(hwnd, uiMsg, wParam, lParam)
endif
    ret

WndProc endp

    assume rbx:THWND

_tmain proc

   .new o:TDIALOG = {0}
   .new t:TEDIT = {0}
   .new b[128]:tchar_t
   .new p:ptr = _conpush()

    paint()
    mov rbx,_console
    mov o.rc,eax
    add o.rc.x,2
    inc o.rc.y
    sub o.rc.col,4
    mov o.rc.row,1
    mov o.window,_rcbprc([rbx].rc, o.rc, [rbx].window)
    mov word ptr [rax],U_MIDDLE_DOT
    mov o.count,lengthof(b)/16
    mov o.flags,O_WNDPROC or O_DEXIT or O_TEDIT or O_USEBEEP or O_AUTOSELECT or O_CHILD or O_MYBUF
    mov o.tedit,&t
    mov t.base,&b
    mov o.buffer,rax
    mov t.bcols,lengthof(b)
    mov o.next,NULL
    mov o.prev,rbx
    mov [rbx].count,1
    mov [rbx].object,&o
    or  [rbx].flags,W_VISIBLE or W_PARENT
    _tcscpy(&b, "string to edit")
    _tcontrol(&o, 128, &b)
    _dlmodal(rbx, &WndProc)
    _conpop(p)
    xor eax,eax
    ret

_tmain endp

    end
