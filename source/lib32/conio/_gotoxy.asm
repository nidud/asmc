; _GOTOXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_gotoxy proc x, y

    mov eax,y
    shl eax,16
    mov ax,word ptr x
    SetConsoleCursorPosition(hStdOutput, eax)
    ret

_gotoxy endp

    END
