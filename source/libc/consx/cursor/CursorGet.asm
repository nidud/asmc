include consx.inc

    .code

CursorGet proc uses ebx cursor:ptr S_CURSOR

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov ebx,cursor

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        mov eax,ci.dwCursorPosition
        mov dword ptr [ebx].S_CURSOR.x,eax
    .endif

    GetConsoleCursorInfo(hStdOutput, ebx)
    mov eax,[ebx].S_CURSOR.bVisible
    ret

CursorGet endp

    END
