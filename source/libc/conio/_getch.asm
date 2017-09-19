include conio.inc
include stdio.inc

.code

_getch proc uses ebx edi esi

local Count:dword
local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi

    .while !edi

        .if GetNumberOfConsoleInputEvents(hStdInput, &Count)

            lea ebx,Event
            mov ecx,Count
            .if ecx > MAXINPUTRECORDS

                mov ecx,MAXINPUTRECORDS
            .endif
            ReadConsoleInput(hStdInput, ebx, ecx, &Count)
            mov esi,Count

            .while esi

                .if [ebx].INPUT_RECORD.EventType == KEY_EVENT && \
                    [ebx].INPUT_RECORD.KeyEvent.bKeyDown

                    movzx edi,[ebx].INPUT_RECORD.KeyEvent.AsciiChar
                    .break .if edi
                .endif

                add ebx,SIZE INPUT_RECORD
                dec esi
            .endw
        .endif
    .endw

    mov eax,edi
    ret

_getch endp

    END
