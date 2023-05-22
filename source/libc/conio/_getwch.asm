; _GETWCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

    .code

_getwch proc uses rbx rdi rsi

ifdef __UNIX__
    .return( -1 )
else
   .new Count:intptr_t
   .new Event[MAXINPUTRECORDS]:INPUT_RECORD
   .new h:HANDLE = _get_osfhandle(_conin)

    xor edi,edi
    .while !edi

        .if GetNumberOfConsoleInputEvents( h, &Count )

            mov rcx,Count
            .if ecx > MAXINPUTRECORDS
                mov ecx,MAXINPUTRECORDS
            .endif

            lea rbx,Event
            ReadConsoleInputW( h, rbx, ecx, &Count )

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
endif

_getwch endp

    end
