; _GETWCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getwch proc uses rbx rdi rsi

  local Count:intptr_t
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    .while !edi

        .if GetNumberOfConsoleInputEvents( _coninpfh, &Count )

            mov rcx,Count
            .if ecx > MAXINPUTRECORDS
                mov ecx,MAXINPUTRECORDS
            .endif

            lea rbx,Event
            ReadConsoleInputW( _coninpfh, rbx, ecx, &Count )

            mov rsi,Count
            .while esi
                .if ( [rbx].INPUT_RECORD.EventType == KEY_EVENT &&
                      [rbx].INPUT_RECORD.Event.KeyEvent.bKeyDown )

                    movzx edi,[rbx].INPUT_RECORD.Event.KeyEvent.uChar.UnicodeChar
                    .break .if edi
                .endif
                add rbx,INPUT_RECORD
                dec esi
            .endw
        .endif
    .endw
    .return( edi )

_getwch endp

    end
