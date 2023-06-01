; RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc

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
    _scputs(1, rc.row, "./rcmove$")
    _cendpaint()
    _gotoxy(11, rc.row)
    ret

paint endp


main proc

   .new rc:TRECT = { 10, 5, 60, 14 }
   .new cr:TRECT = {  0, 0, 60, 14 }
   .new p:PCHAR_INFO = _rcalloc(rc, 0)

    mov rdi,p
    mov eax,(AT shl 16) or ' '
    mov ecx,60*14
    rep stosd

    paint()

    _rcframe(rc, cr, p, BOX_DOUBLE, 0)
    _rcputs(rc, p, 2, 2, 0, "Use Left, Right, Up, or Down to Move")
    _rcxchg(rc, p)

    .while 1

        .switch _getkey()
        .case VK_RETURN
        .case VK_ESCAPE
            .break
        .case KEY_LEFT
            mov rc,_rcmovel(rc, p)
           .endc
        .case KEY_RIGHT
            mov rc,_rcmover(rc, p)
           .endc
        .case KEY_UP
            mov rc,_rcmoveu(rc, p)
           .endc
        .case KEY_DOWN
            mov rc,_rcmoved(rc, p)
           .endc
        .endsw
    .endw
    _rcxchg(rc, p)
    .return(0)
main endp

    end
