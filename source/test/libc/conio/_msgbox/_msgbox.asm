; _MSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include tchar.inc

.code

paint proc uses rbx

   .new rc:TRECT
   .new fc:TRECT = { 2, 10, 51, 3 }

    mov rcx,_console
    mov rc,[rcx].TCLASS.rc

    _cbeginpaint()
    _scputa(0, 0, rc.col, 0x47)
    mov al,rc.col
    shr al,1
    sub al,12
    _scputs(al, 0, "Virtual Terminal Sample")

    _scputs(1, 10, "_msgboxA proto __Cdecl :uint_t, :string_t, :string_t, :vararg")
    _scputs(1, 11, "_msgboxW proto __Cdecl :uint_t, :wstring_t, :wstring_t, :vararg")

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
    _scputs(1, rc.row, "./_msgbox$")
    _cendpaint()
    _gotoxy(11, rc.row)
    ret

paint endp

_tmain proc argc:int_t, argv:array_t

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

_tmain endp

    end
