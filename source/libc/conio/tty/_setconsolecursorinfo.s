; _SETCONSOLECURSORINFO.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include consoleapi.inc

.code

_setconsolecursorinfo proc WINAPI uses rbx fh:HANDLE, cp:PCONSOLE_CURSOR_INFO

    ldr rbx,cp

    mov rcx,_console
    mov [rcx].TCONSOLE.cvisible,[rbx].CONSOLE_CURSOR_INFO.bVisible
    mov eax,[rbx].CONSOLE_CURSOR_INFO.dwSize

    .if ( eax != [rcx].TCONSOLE.csize )

        .if ( eax > CURSOR_BAR )
            mov eax,CURSOR_DEFAULT
        .endif
        mov [rcx].TCONSOLE.csize,eax
        _cout(CSI "%d q", eax)
    .endif
    .if ( [rbx].CONSOLE_CURSOR_INFO.bVisible )
        _cout(CSI "?25h")
    .else
        _cout(CSI "?25l")
    .endif
    mov eax,1
    ret

_setconsolecursorinfo endp

    end
