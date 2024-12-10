; _GETCONSOLECURSORINFO.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include consoleapi.inc

.code

_getconsolecursorinfo proc WINAPI fh:HANDLE, cp:PCONSOLE_CURSOR_INFO

    ldr rdx,cp

    mov rcx,_console
    mov eax,[rcx].TCONSOLE.csize
    mov [rdx].CONSOLE_CURSOR_INFO.dwSize,eax
    mov eax,[rcx].TCONSOLE.cvisible
    mov [rdx].CONSOLE_CURSOR_INFO.bVisible,eax
    mov eax,1
    ret

_getconsolecursorinfo endp

    end
