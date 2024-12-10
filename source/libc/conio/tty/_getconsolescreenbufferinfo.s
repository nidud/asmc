; _GETCONSOLESCREENBUFFERINFO.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include consoleapi.inc

    .code

    assume rbx:PCONSOLE_SCREEN_BUFFER_INFO

_getconsolescreenbufferinfo proc WINAPI uses rbx fh:HANDLE, pc:PCONSOLE_SCREEN_BUFFER_INFO

   .new a:AnsiEscapeCode

    ldr rbx,pc

    xor eax,eax
    mov [rbx].wAttributes,ax
    mov [rbx].srWindow.Top,ax
    mov [rbx].srWindow.Left,ax
    mov [rbx].dwCursorPosition,eax
    mov [rbx].dwSize,eax

    _cout(CSI "6n") ; get cursor
    .ifd ( _readansi( &a ) && a.count == 2 )

        mov eax,a.n
        mov ecx,a.n[4]
        .if ( eax )
            dec eax
        .endif
        .if ( ecx )
            dec ecx
        .endif
        mov [rbx].dwCursorPosition.Y,ax
        mov [rbx].dwCursorPosition.X,cx
    .endif

    _cout(ESC "7" CSI "256;256H" CSI "6n")
    .ifd ( _readansi( &a ) && a.count == 2 )

        mov eax,a.n
        mov ecx,a.n[4]
        mov [rbx].dwSize.Y,ax
        mov [rbx].dwSize.X,cx
        mov [rbx].dwMaximumWindowSize.Y,ax
        mov [rbx].dwMaximumWindowSize.X,cx
        .if ( eax )
            dec eax
        .endif
        .if ( ecx )
            dec ecx
        .endif
        mov [rbx].srWindow.Bottom,ax
        mov [rbx].srWindow.Right,cx
    .endif
    _cout(ESC "8" )
    mov eax,1
    ret

_getconsolescreenbufferinfo endp

    end
