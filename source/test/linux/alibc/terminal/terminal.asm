; TERMINAL.ASM--
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
    _scputs(1, rc.row, "./terminal$")
    _cendpaint()
    _gotoxy(13, rc.row)
    ret

paint endp


setn proto :string_t {
    mov n,rdi
    }

main proc

   .new p:int_t = 0
   .new c:int_t = 0
   .new y:byte = 0
   .new n:string_t = 0
   .new keys:CINPUT

    paint()

    _cout(CSI "0c" ) ; read terminal identity
    .repeat

        .break .if ( _getch() != VK_ESCAPE )
        .break .if ( _getch() != '[' )
        .break .if ( _getch() != '?' )

        mov p,_getch()
        mov c,_getch()

        .if ( p == '1' )

            .if ( c == ';' )

                mov c,_getch()
            .endif
            .if ( eax != 'c' )
                _getch() ; c
            .endif
            .if ( c == '0' )
                setn("VT101 with No Options")
            .else
                setn("VT100 with Advanced Video Option")
            .endif
            .break
        .endif

        .switch c
        .case '2'
            setn("VT220")
           .endc
        .case '3'
            setn("VT320")
           .endc
        .case '4'
            setn("VT420")
           .endc
        .default
            setn("VT102")
           .break
        .endsw
        mov y,4
    .until 1

    _scputf(2, 2, "Terminal type: %s", n)
    _scputs(2, 3, "Supported features:")

    .if ( y )

        mov c,_getch()

        .while ( c != 'c' )

            inc y
            mov eax,c
            .if ( eax == ';' )
                mov c,_getch()
            .endif
            xor ebx,ebx
            .if ( eax >= '0' && eax <= '9' )

                sub eax,'0'
                mov ebx,eax
                mov c,_getch()
            .endif
            .if ( eax >= '0' && eax <= '9' )

                imul ebx,ebx,10
                sub eax,'0'
                add ebx,eax
                mov c,_getch()
            .endif

            .switch pascal ebx
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
        .endw
    .endif

    mov rcx,_console
    mov al,[rcx].TCLASS.rc.row
    dec al
    mov y,al

    .whiled ( _getch() != -1 )

        .if ( eax != VK_ESCAPE )

           .break .if ( eax == VK_RETURN )
            mov keys.q,rax
        .elseif ( _kbflush() == 0 )
           .break
        .else
            mov keys.q,rcx
        .endif
        _scputf(13, y, "%-8s", &keys.b)
    .endw
    .return(0)

main endp

    end
