; _GOTOXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    option win64:nosave

_gotoxy proc x:UINT, y:UINT

    shl edx,16
    or  edx,ecx
    SetConsoleCursorPosition(hStdOutput, edx)
    ret

_gotoxy endp

    end
