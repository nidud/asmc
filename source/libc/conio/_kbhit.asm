; _KBHIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

    ASSUME rbx:PTR INPUT_RECORD

_kbhit PROC USES rbx rdi rsi

  local Count:intptr_t
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    lea rbx,Event

    .if GetNumberOfConsoleInputEvents(_coninpfh, &Count)

        mov rcx,Count
        .if rcx > MAXINPUTRECORDS
            mov rcx,MAXINPUTRECORDS
        .endif

        PeekConsoleInput( _coninpfh, rbx, ecx, &Count )
        mov rsi,Count

        .while esi

            .if ( [rbx].EventType == KEY_EVENT && [rbx].Event.KeyEvent.bKeyDown )

                movzx edi,[rbx].Event.KeyEvent.uChar.AsciiChar
                .break .if edi
            .endif

            ReadConsoleInput( _coninpfh, rbx, 1, &Count )
            add rbx,INPUT_RECORD
            dec esi
        .endw
    .endif
    .return( edi )

_kbhit endp

    end
