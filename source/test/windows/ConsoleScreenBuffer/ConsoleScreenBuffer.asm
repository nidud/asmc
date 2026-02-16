; CONSOLESCREENBUFFER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include winbase.inc
include tchar.inc

.code

ConsoleScreenBuffer proc

   .new ci:CONSOLE_SCREEN_BUFFER_INFOEX = {CONSOLE_SCREEN_BUFFER_INFOEX}

    .if GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &ci)

        printf(
            "CONSOLE_SCREEN_BUFFER_INFOEX:\n"
            " .cbSize               %u\n"
            " .dwSize:\n"
            "  .X                   %u\n"
            "  .Y                   %u\n"
            " .dwCursorPosition:\n"
            "  .X                   %u\n"
            "  .Y                   %u\n"
            " .wAttributes          %u\n"
            " .srWindow:\n"
            "  .Left                %u\n"
            "  .Top                 %u\n"
            "  .Right               %u\n"
            "  .Bottom              %u\n"
            " .dwMaximumWindowSize:\n"
            "  .X                   %u\n"
            "  .Y                   %u\n"
            " .wPopupAttributes     %#X\n"
            " .bFullscreenSupported %u\n"
            " .ColorTable:\n"
            "  .0 %08X  .8 %08X\n"
            "  .1 %08X  .9 %08X\n"
            "  .2 %08X  .A %08X\n"
            "  .3 %08X  .B %08X\n"
            "  .4 %08X  .C %08X\n"
            "  .5 %08X  .D %08X\n"
            "  .6 %08X  .E %08X\n"
            "  .7 %08X  .F %08X\n",
            ci.cbSize,
            ci.dwSize.X,
            ci.dwSize.Y,
            ci.dwCursorPosition.X,
            ci.dwCursorPosition.Y,
            ci.wAttributes,
            ci.srWindow.Left,
            ci.srWindow.Top,
            ci.srWindow.Right,
            ci.srWindow.Bottom,
            ci.dwMaximumWindowSize.X,
            ci.dwMaximumWindowSize.Y,
            ci.wPopupAttributes,
            ci.bFullscreenSupported,
            ci.ColorTable[0x00*4],
            ci.ColorTable[0x08*4],
            ci.ColorTable[0x01*4],
            ci.ColorTable[0x09*4],
            ci.ColorTable[0x02*4],
            ci.ColorTable[0x0A*4],
            ci.ColorTable[0x03*4],
            ci.ColorTable[0x0B*4],
            ci.ColorTable[0x04*4],
            ci.ColorTable[0x0C*4],
            ci.ColorTable[0x05*4],
            ci.ColorTable[0x0D*4],
            ci.ColorTable[0x06*4],
            ci.ColorTable[0x0E*4],
            ci.ColorTable[0x07*4],
            ci.ColorTable[0x0F*4])
    .endif
    ret
    endp

_tmain proc
    ConsoleScreenBuffer()
   .return( 0 )
    endp

    end _tstart
