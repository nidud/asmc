include conio.inc

    .code

_wherey proc
local ci:CONSOLE_SCREEN_BUFFER_INFO

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        movzx eax,ci.dwCursorPosition.y
    .endif
    ret
_wherey endp

    END
