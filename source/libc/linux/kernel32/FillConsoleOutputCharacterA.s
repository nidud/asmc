; FILLCONSOLEOUTPUTCHARACTERA.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consoleapi2.inc

.code

 FillConsoleOutputCharacterA proc WINAPI hConsoleOutput:HANDLE,
        cCharacter:CHAR, nLength:DWORD, dwWriteCoord:COORD, lpNumberOfCharsWritten:LPDWORD
    .return( FillConsoleOutputCharacterW(
                ldr(hConsoleOutput),
                ldr(cCharacter),
                ldr(nLength),
                ldr(dwWriteCoord),
                ldr(lpNumberOfCharsWritten) ) )
    endp

    end
