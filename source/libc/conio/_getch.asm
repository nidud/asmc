; _GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getch proc uses rbx rdi rsi

  local Count:intptr_t
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    .while !edi

        .if GetNumberOfConsoleInputEvents( hStdInput, &Count )

            mov rcx,Count
            .if ecx > MAXINPUTRECORDS
                mov ecx,MAXINPUTRECORDS
            .endif

            lea rbx,Event
            ReadConsoleInput( hStdInput, rbx, ecx, &Count )

            mov rsi,Count
            .while esi

                .if ( [rbx].INPUT_RECORD.EventType == KEY_EVENT &&
                      [rbx].INPUT_RECORD.KeyEvent.bKeyDown )

                    movzx edi,[rbx].INPUT_RECORD.KeyEvent.AsciiChar
                    .break .if edi
                .endif
                add rbx,INPUT_RECORD
                dec esi
            .endw
        .endif
        Sleep( 1 )
    .endw
    .return( edi )

_getch endp

    end
