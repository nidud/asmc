; _TREADINPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

_readinput proc Input:PINPUT_RECORD
    .new Count:dword
    .new NumberOfEventsRead:dword
    .ifd !GetNumberOfConsoleInputEvents(_coninpfh, &Count)
        dec rax
    .else
        mov eax,Count
        .if ( eax )
            .ifd !ReadConsoleInput(_coninpfh, Input, 1, &NumberOfEventsRead)
                dec rax
            .else
                mov eax,NumberOfEventsRead
            .endif
        .endif
    .endif
    ret
    endp

    end
