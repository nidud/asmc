; FILLCONSOLEOUTPUTATTRIBUTE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include conio.inc
include consoleapi2.inc

.code

 FillConsoleOutputAttribute proc WINAPI uses rbx hConsoleOutput:HANDLE,
        wAttribute:WORD, nLength:DWORD, dwWriteCoord:COORD, lpNumberOfAttrsWritten:LPDWORD
   .new x:int_t
   .new y:int_t
   .new ci:CONSOLE_CURSOR_INFO
    ldr rbx,hConsoleOutput
    ldr eax,dwWriteCoord
    movzx ecx,ax
    inc ecx
    mov x,ecx
    shr eax,16
    inc eax
    mov y,eax
    mov rdx,lpNumberOfAttrsWritten
    .if ( rdx )
        mov eax,ldr(nLength)
        mov [rdx],eax
    .endif
    GetConsoleCursorInfo(NULL, &ci)
    fprintf(rbx, ESC "7")
    .if ( ci.bVisible )
        fprintf(rbx, CSI "?25l")
    .endif
    movzx eax,byte ptr wAttribute
    mov ecx,eax
    and eax,0x0F
    shr ecx,4
    lea rdx,_terminalcolorid
    mov al,[rdx+rax]
    mov cl,[rdx+rcx]
    fprintf(rbx, CSI "%d;%dH" CSI "38;5;%dm" CSI "48;5;%dm", y, x, eax, ecx)
    .if ( nLength )
        fprintf(rbx, CSI "%dX" CSI "m", nLength)
    .else
        fprintf(rbx, CSI "m")
    .endif
    fprintf(rbx, ESC "8")
    .if ( ci.bVisible )
        fprintf(rbx, CSI "?25h")
    .endif
    fflush(rbx)
    .return( 1 )
    endp

    end

