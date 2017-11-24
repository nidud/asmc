include conio.inc

    .code

    option win64:rsp nosave

_gotoxy PROC x, y
    mov eax,edx
    shl eax,16
    mov ax,cx
    SetConsoleCursorPosition(hStdOutput, eax)
    ret
_gotoxy ENDP

    END
