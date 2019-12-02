; CURSORSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

CursorSet proc uses eax Cursor:ptr S_CURSOR

    mov eax,Cursor
    mov eax,dword ptr [eax].S_CURSOR.x

    SetConsoleCursorPosition(hStdOutput, eax)
    SetConsoleCursorInfo(hStdOutput, Cursor)
    ret

CursorSet endp

    END