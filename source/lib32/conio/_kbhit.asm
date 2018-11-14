; _KBHIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

externdef char_avail:dword
externdef ungot_char:dword

    .code

    assume ebx:ptr INPUT_RECORD

_kbhit proc uses ebx edi esi

  local Count:dword
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

    xor edi,edi
    lea ebx,Event

    .if char_avail

        mov edi,ungot_char

    .elseif GetNumberOfConsoleInputEvents(hStdInput, &Count)

        mov ecx,Count
        .if ecx > MAXINPUTRECORDS

            mov ecx,MAXINPUTRECORDS
        .endif

        PeekConsoleInput(hStdInput, ebx, ecx, &Count)

        mov esi,Count
        .while  esi

            .if [ebx].INPUT_RECORD.EventType == KEY_EVENT && \
                [ebx].INPUT_RECORD.KeyEvent.bKeyDown

                movzx edi,[ebx].INPUT_RECORD.KeyEvent.AsciiChar
                .break .if edi
            .endif

            ReadConsoleInput(hStdInput, ebx, 1, &Count)

            add ebx,SIZE INPUT_RECORD
            dec esi
        .endw
    .endif

    mov eax,edi
    ret

_kbhit endp

    END
