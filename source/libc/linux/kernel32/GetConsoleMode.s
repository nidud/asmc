; GETCONSOLEMODE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.data
 current_mode dd 0
.code

GetConsoleMode proc WINAPI hConsoleHandle:HANDLE, lpMode:LPDWORD
    ldr rdx,lpMode
    mov eax,current_mode
    mov [rdx],eax
    .return( TRUE )
    endp

SetConsoleMode proc WINAPI hConsoleHandle:HANDLE, dwMode:DWORD
    ldr edx,dwMode
    mov eax,current_mode
    mov current_mode,edx
    .if ( edx & ENABLE_MOUSE_INPUT && !( eax & ENABLE_MOUSE_INPUT ) )
        _write(_confd, SET_ANY_EVENT_MOUSE, 8)
    .elseif ( eax & ENABLE_MOUSE_INPUT && !( edx & ENABLE_MOUSE_INPUT ) )
        _write(_confd, RST_ANY_EVENT_MOUSE, 8)
    .endif
    .return( TRUE )
    endp

    end
