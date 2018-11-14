; _GETCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getch proc uses rbx rdi rsi

  local Count:QWORD
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    .while !edi

        .if GetNumberOfConsoleInputEvents(hStdInput, &Count)

            mov r8,Count
            .if r8 > MAXINPUTRECORDS
                mov r8,MAXINPUTRECORDS
            .endif

            lea rbx,Event
            ReadConsoleInput(hStdInput, rbx, r8d, &Count)

            mov rsi,Count
            .while esi

                .if [rbx].INPUT_RECORD.EventType == KEY_EVENT && \
                    [rbx].INPUT_RECORD.KeyEvent.bKeyDown

                    movzx edi,[rbx].INPUT_RECORD.KeyEvent.AsciiChar
                    .break .if edi
                .endif
                add rbx,SIZE INPUT_RECORD
                dec esi
            .endw
        .endif
    .endw
    mov eax,edi
    ret
_getch endp

    end
