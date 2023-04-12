; _MSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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
    sub sil,9
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

    add fc.y,4
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
    _scputs(1, rc.row, "./msgbox$")
    _cendpaint()
    _gotoxy(11, rc.row)
    ret

paint endp

main proc

    paint()

    _msgbox(MB_CANCELTRYCONTINUE or MB_DEFBUTTON3,
            "_msgbox()",
            "MB_CANCELTRYCONTINUE or MB_DEFBUTTON3\n"
            "\n"
            "Return value:    \n"
            "\n"
            "IDCANCEL      %2d\n"
            "IDTRYAGAIN    %2d\n"
            "IDCONTINUE    %2d\n",
            IDCANCEL, IDTRYAGAIN, IDCONTINUE )

    _msgbox(MB_OK or MB_USERICON, "_msgbox()", "return value: %d", eax )

    .return(0)

main endp

    end
