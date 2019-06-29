; TCONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .code

TWindow::MoveConsole proc uses rcx x:int_t, y:int_t

    SetWindowPos( GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER )
    ret

TWindow::MoveConsole endp

    assume rcx:window_t
    assume rbx:window_t
    assume rsi:class_t

TWindow::SetConsole proc uses rsi rbx rcx cols:int_t, rows:int_t

  local bz:COORD
  local rc:SMALL_RECT
  local ci:CONSOLE_SCREEN_BUFFER_INFO

    mov rsi,[rcx].Class
    mov rcx,[rsi].Console

    movzx   eax,[rcx].rc.x
    mov     bz.x,dx
    mov     bz.y,r8w
    mov     rc.Left,ax
    add     eax,edx
    dec     eax
    mov     rc.Right,ax
    movzx   eax,[rcx].rc.y
    add     eax,r8d
    dec     eax
    mov     rc.Bottom,ax

    .ifd GetConsoleScreenBufferInfo([rsi].StdOut, &ci)

        SetConsoleWindowInfo([rsi].StdOut, 1, &rc)
        SetConsoleScreenBufferSize([rsi].StdOut, bz)
        SetConsoleWindowInfo([rsi].StdOut, 1, &rc)

        .if GetConsoleScreenBufferInfo([rsi].StdOut, &ci)

            mov     rbx,[rsi].Console
            movzx   eax,ci.dwSize.y
            mov     [rbx].rc.row,al
            movzx   ecx,ci.dwSize.x
            mov     [rbx].rc.col,cl
            mul     ecx

            .if malloc(&[rax*4])

                mov rcx,[rbx].Window
                mov [rbx].Window,rax
                free(rcx)
                or [rbx].Flags,W_ISOPEN
                [rbx].Read()
                mov eax,1
            .endif
        .endif
    .endif
    ret

TWindow::SetConsole endp

TWindow::SetMaxConsole proc uses rsi rcx

    mov rsi,[rcx].Class
    mov rcx,[rsi].Console

    [rcx].MoveConsole(0, 0)
    GetLargestConsoleWindowSize([rsi].StdOut)
    mov rcx,[rsi].Console

    mov edx,eax
    shr eax,16
    and edx,0xFFFF

    .if ( edx < 80 || eax < 16 )
        mov edx,80
        mov eax,25
    .elseif ( edx > 255 || eax > 255 )
        .if ( edx > 255 )
            mov edx,240
        .endif
        .if ( eax > 255 )
            mov eax,240
        .endif
    .endif
    [rcx].SetConsole(edx, eax)
    ret

TWindow::SetMaxConsole endp

TWindow::ConsoleSize proc uses rcx

    mov     rax,[rcx].Class
    mov     rcx,[rax].APPINFO.Console
    movzx   edx,[rcx].rc.row
    mov     eax,edx
    shl     eax,16
    mov     al,[rcx].rc.col
    ret

TWindow::ConsoleSize endp

    end
