; FILLCONSOLEOUTPUTCHARACTERW.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include conio.inc
include consoleapi2.inc

.code

 FillConsoleOutputCharacterW proc WINAPI uses rbx hConsoleOutput:HANDLE,
        cCharacter:WCHAR, nLength:DWORD, dwWriteCoord:COORD, lpNumberOfCharsWritten:LPDWORD

   .new x:int_t
   .new y:int_t
   .new wc:int_t
   .new wclen:int_t
   .new ci:CONSOLE_CURSOR_INFO
    ldr rbx,hConsoleOutput
    ldr eax,dwWriteCoord
    movzx ecx,ax
    inc ecx
    mov x,ecx
    shr eax,16
    inc eax
    mov y,eax
    mov rdx,lpNumberOfCharsWritten
    .if ( rdx )
        mov eax,ldr(nLength)
        mov [rdx],eax
    .endif
    GetConsoleCursorInfo(NULL, &ci)
    fprintf(rbx, ESC "7")
    .if ( ci.bVisible )
        fprintf(_confh, CSI "?25l")
    .endif
    fprintf(rbx, CSI "%d;%dH", y, x)
    movzx ecx,cCharacter
    mov wc,_wtoutf(ecx)
    mov wclen,ecx
    .for ( : nLength : nLength-- )
        fwrite(&wc, 1, wclen, rbx)
    .endf
    fprintf(rbx, ESC "8")
    .if ( ci.bVisible )
        fprintf(rbx, CSI "?25h")
    .endif
    fflush(rbx)
    .return( 1 )
    endp

    end
