; TTYAPI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdlib.inc

.code

ifdef __TTY__

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
        fprintf(_confp, CSI "%d q", eax)
    .endif
    .if ( [rbx].CONSOLE_CURSOR_INFO.bVisible )
        fprintf(_confp, CSI "?25h")
    .else
        fprintf(_confp, CSI "?25l")
    .endif
    fflush(_confp)
    mov eax,1
    ret

_setconsolecursorinfo endp

_setconsolecursorposition proc WINAPI fh:HANDLE, pos:COORD

    ldr     edx,pos
    mov     ecx,edx
    shr     edx,16
    movzx   ecx,cx
    inc     ecx
    inc     edx
    fprintf(_confp, CSI "%d;%dH", edx, ecx)
    fflush(_confp)
    ret

_setconsolecursorposition endp

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

    _write(_confd, CSI "6n", 4) ; get cursor
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

    _write(_confd, ESC "7" CSI "256;256H" CSI "6n", 16)
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
    _write(_confd, ESC "8", 2)
    mov eax,1
    ret

_getconsolescreenbufferinfo endp

    assume rbx:PCONSOLE_SCREEN_BUFFER_INFOEX

_getconsolescreenbufferinfoex proc WINAPI uses rsi rdi rbx fh:HANDLE, pc:PCONSOLE_SCREEN_BUFFER_INFOEX

    ldr rbx,pc
    ldr rcx,fh

    _getconsolescreenbufferinfo( rcx, &[rbx].dwSize )
    mov [rbx].wPopupAttributes,0
    mov [rbx].bFullscreenSupported,1
    lea rdi,[rbx].ColorTable
    lea rsi,_rgbcolortable
    mov ecx,16
    rep movsd
    mov eax,1
    ret

_getconsolescreenbufferinfoex endp

_writeconsoleoutputw proc WINAPI uses rbx hConsoleOutput:HANDLE, lpBuffer:PCHAR_INFO,
        dwBufferSize:COORD, dwBufferCoord:COORD, lpWriteRegion:PSMALL_RECT

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new cols:int_t
   .new wc:int_t
   .new color_changed:int_t = 0
   .new foreground:int_t = 0
   .new background:int_t = 0

    ldr rbx,lpBuffer
    ldr rcx,lpWriteRegion

    movzx   eax,[rcx].SMALL_RECT.Left
    inc     eax
    mov     x,eax
    movzx   eax,[rcx].SMALL_RECT.Top
    inc     eax
    mov     y,eax
    mov     ax,[rcx].SMALL_RECT.Right
    sub     ax,[rcx].SMALL_RECT.Left
    inc     eax
    mov     cols,eax

    fprintf(_confp, CSI "%d;%dH", y, x)

    .for ( l = cols : l : l--, rbx += 4 )

        movzx   eax,byte ptr [rbx+2]
        mov     ecx,eax
        and     eax,0x0F
        shr     ecx,4

        .if ( eax != foreground || ecx != background )

            mov color_changed,1
            mov foreground,eax
            mov background,ecx

            lea rdx,_terminalcolorid
            mov al,[rdx+rax]
            mov cl,[rdx+rcx]
            fprintf(_confp, CSI "38;5;%dm" CSI "48;5;%dm", eax, ecx)
        .endif
        mov wc,_wtoutf([rbx])
        mov edx,ecx
        fwrite(&wc, 1, edx, _confp)
    .endf
    .if ( color_changed )
        fprintf(_confp, CSI "m")
    .endif
    mov eax,1
    ret

_writeconsoleoutputw endp

endif

    end
