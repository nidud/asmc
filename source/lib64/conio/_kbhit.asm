; _KBHIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include stdio.inc

    .code

    ASSUME rbx:PTR INPUT_RECORD

_kbhit PROC USES rbx rdi rsi

  local Count:QWORD
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    lea rbx,Event

    .if GetNumberOfConsoleInputEvents(hStdInput, &Count)

        mov r8,Count
        .if r8 > MAXINPUTRECORDS
            mov r8,MAXINPUTRECORDS
        .endif

        PeekConsoleInput(hStdInput, rbx, r8d, &Count)
        mov rsi,Count

        .while esi

            .if [rbx].EventType == KEY_EVENT && [rbx].KeyEvent.bKeyDown

                movzx edi,[rbx].KeyEvent.AsciiChar
                .break .if edi
            .endif

            ReadConsoleInput(hStdInput, rbx, 1, &Count)
            add rbx,SIZE INPUT_RECORD
            dec esi
        .endw
    .endif
    mov eax,edi
    ret
_kbhit endp

    end
