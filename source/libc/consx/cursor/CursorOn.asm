include consx.inc

    .code

CursorOn proc uses eax
local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    SetConsoleCursorInfo(hStdOutput, &cu)
    ret

CursorOn endp

    END
