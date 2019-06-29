; TCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t
    assume rdi:cursor_t
    assume rsi:class_t

TWindow::CursorGet proc uses rsi rdi rbx rcx

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rbx,rcx
    mov rsi,[rcx].Class
    mov rax,[rcx].Cursor

    .return .if ( rax != NULL )
    .return .if !malloc(sizeof(TCURSOR))

    mov [rbx].Cursor,rax
    mov rdi,rax
    mov [rdi].Position,0
    .if GetConsoleScreenBufferInfo([rsi].StdOut, &ci)
        mov [rdi].Position,ci.dwCursorPosition
    .endif
    GetConsoleCursorInfo([rsi].StdOut, rdi)
    mov rax,rdi
    ret

TWindow::CursorGet endp

TWindow::CursorSet proc uses rsi rdi rbx

    mov rax,[rcx].Cursor
    .return .if ( rax == NULL )

    mov rdi,rax
    mov rsi,[rcx].Class
    mov rbx,rcx

    SetConsoleCursorPosition([rsi].StdOut, [rdi].Position)
    SetConsoleCursorInfo([rsi].StdOut, rdi)
    free(rdi)

    mov rcx,rbx
    xor eax,eax
    mov [rcx].Cursor,rax
    ret

TWindow::CursorSet endp

    assume rcx:nothing

TWindow::CursorOn proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,1
    mov rcx,[rcx].TWindow.Class
    SetConsoleCursorInfo([rcx].APPINFO.StdOut, &cu)
    ret

TWindow::CursorOn endp

TWindow::CursorOff proc uses rcx

  local cu:CONSOLE_CURSOR_INFO

    mov cu.dwSize,CURSOR_NORMAL
    mov cu.bVisible,0
    mov rcx,[rcx].TWindow.Class
    SetConsoleCursorInfo([rcx].APPINFO.StdOut, &cu)
    ret

TWindow::CursorOff endp

TWindow::CursorMove proc uses rcx x:int_t, y:int_t

    shl r8d,16
    or  edx,r8d
    mov rcx,[rcx].TWindow.Class
    SetConsoleCursorPosition([rcx].APPINFO.StdOut, edx)
    ret

TWindow::CursorMove endp

    end
