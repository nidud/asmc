; SETCONSOLESCREENBUFFERSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Sets the current size and position of a console screen buffer's window.
;

include stdio.inc
include conio.inc

.data
 g_ConsoleScreenBufferSize COORD <>

.code

SetConsoleScreenBufferSize proc WINAPI fp:HANDLE, dwSize:COORD

    mov g_ConsoleScreenBufferSize,ldr(dwSize)

    fprintf(fp, "\e]4;0;rgb:00/00/00\e\\\e]4;7;rgb:AA/AA/AA\e\\")
    fprintf(fp, "\e[48;5;0m")
    fprintf(fp, "\e[38;5;7m")
    fflush(fp)
    ret
    endp

    end
