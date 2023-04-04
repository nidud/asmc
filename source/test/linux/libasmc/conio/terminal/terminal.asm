; TERMINAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

main proc

   .new p:int_t = 0
   .new c:int_t = 0

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
                _cout( "VT101 with No Options\n" )
            .else
                _cout( "VT100 with Advanced Video Option\n" )
            .endif
            .return( 0 )
        .endif

        .switch c
        .case '2'
            _cout( "VT220\n" )
            .endc
        .case '3'
            _cout( "VT320\n" )
            .endc
        .case '4'
            _cout( "VT420\n" )
            .endc
        .default
            _cout( "VT102\n" )
            .return( 0 )
        .endsw

        _cout( "\nFeatures the terminal supports:\n" )
        mov c,_getch()

        .while ( c != 'c' )

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
            .case  1: _cout( "132-columns\n" )
            .case  2: _cout( "Printer\n" )
            .case  3: _cout( "ReGIS graphics\n" )
            .case  4: _cout( "Sixel graphics\n" )
            .case  6: _cout( "Selective erase\n" )
            .case  8: _cout( "User-defined keys\n" )
            .case  9: _cout( "National Replacement Character sets.\n" )
            .case 15: _cout( "Technical characters\n" )
            .case 18: _cout( "User windows\n" )
            .case 21: _cout( "Horizontal scrolling\n" )
            .case 22: _cout( "ANSI color, e.g., VT525\n" )
            .case 29: _cout( "ANSI text locator (i.e., DEC Locator mode)\n" )
            .default
            .break
            .endsw
        .endw
        .return( 0 )
    .until 1
    _cout("error: not a terminal device\n" )
   .return(0)

main endp

    end
