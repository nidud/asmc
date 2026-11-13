; SETCONSOLEWINDOWINFO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
.data
 rcConsoleWindow SMALL_RECT <>
.code

SetConsoleWindowInfo proc WINAPI hConsoleOutput:HANDLE, bAbsolute:BOOL, lpConsoleWindow:PSMALL_RECT
    ldr rdx,lpConsoleWindow
    mov rcConsoleWindow,[rdx]
    ret
    endp

    end
