; TEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .code

    assume rdx:msg_t

Dispatch proc private uses rcx hwnd:window_t, msg:msg_t

    mov rcx,[rcx].TWindow.Class
    mov r8,[rdx].Next
    mov rax,[rcx].APPINFO.Message

    .if ( rax == rdx )
        mov [rcx].APPINFO.Message,r8
    .elseif rax
        .while ( rax && rdx != [rax].TMESSAGE.Next )
            mov rax,[rax].TMESSAGE.Next
        .endw
        .if ( rax && rdx == [rax].TMESSAGE.Next )
            mov [rax].TMESSAGE.Next,r8
        .endif
    .endif
    free(rdx)
    ret

Dispatch endp


    assume rcx:window_t

Translate proc private uses rdi rcx hwnd:window_t, msg:msg_t

    mov edi,[rdx].Message
    mov [rdx].Message,WM_NULL

    [rcx].Send(edi, [rdx].wParam, [rdx].lParam)

    mov rcx,hwnd
    .return .if ( edi != WM_KEYDOWN )

    mov rdx,msg
    mov r8,[rdx].wParam
    mov r9,[rdx].lParam
    mov edx,WM_CHAR
    .if ( r9d & RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED )
        mov edx,WM_SYSCHAR
    .endif
    [rcx].Send(edx, r8, r9)
    ret

Translate endp


TWindow::Send proc uses rcx uiMsg:uint_t, wParam:size_t, lParam:ptr

    .for ( eax = 1 : rcx : )

        .if ( [rcx].Flags & W_WNDPROC )

            .break .ifd ( [rcx].WndProc(rcx, edx, r8, r9) != 1 )

            mov rcx,this
            mov edx,uiMsg
            mov r8,wParam
            mov r9,lParam
        .endif
        .if ( [rcx].Flags & W_CHILD )
            mov rcx,[rcx].Child
        .else
            mov rcx,[rcx].PrevInst
        .endif
        mov this,rcx
    .endf
    ret

TWindow::Send endp


    assume r10:class_t

TWindow::Post proc uiMsg:uint_t, wParam:size_t, lParam:ptr

    .return .if !malloc(TMESSAGE)

    mov rdx,rax
    mov [rdx].Next,0
    mov [rdx].Message,uiMsg
    mov [rdx].wParam,wParam
    mov [rdx].lParam,lParam
    mov rcx,this
    mov r10,[rcx].Class
    mov rax,rdx

    mov rdx,[r10].Message
    .for ( : rdx && [rdx].Next : rdx = [rdx].Next )

    .endf
    .if rdx
        mov [rdx].Next,rax
    .else
        mov [r10].Message,rax
    .endif
    ret

TWindow::Post endp


    assume r10:nothing

TWindow::PostQuit proc uses rcx retval:int_t

    test [rcx].Flags,W_CHILD
    cmovnz rcx,[rcx].PrevInst
    [rcx].Post(WM_QUIT, retval, 0)
    xor eax,eax
    ret

TWindow::PostQuit endp


    assume rdx:nothing
    assume rbx:window_t
    assume rsi:class_t

TWindow::Register proc uses rsi rdi rbx tproc:tproc_t

  local Count:dword
  local Event:INPUT_RECORD
  local hPrev:window_t
  local IdleCount:dword
  local EventCount:dword

    mov [rcx].WndProc,rdx
    or  [rcx].Flags,W_WNDPROC
    mov IdleCount,0
    mov rsi,[rcx].Class
    mov hPrev,[rsi].Instance
    mov [rsi].Instance,rcx
    [rcx].WndProc(rcx, WM_CREATE, 0, 0)

    .while 1

        assume rdi:ptr INPUT_RECORD

        lea rdi,Event
        .if GetNumberOfConsoleInputEvents([rsi].StdIn, &EventCount)

            .while EventCount

                ReadConsoleInput([rsi].StdIn, rdi, 1, &Count)

                .break .if !Count

                .switch pascal [rdi].EventType

                  .case KEY_EVENT

                    mov edx,WM_KEYUP
                    .if [rdi].KeyEvent.bKeyDown

                        mov edx,WM_KEYDOWN
                    .endif

                    movzx   r8d,[rdi].KeyEvent.wVirtualKeyCode
                    movzx   eax,[rdi].KeyEvent.AsciiChar
                    shl     rax,56
                    or      r8,rax
                    mov     r9d,[rdi].KeyEvent.dwControlKeyState
                    movzx   eax,[rdi].KeyEvent.wVirtualScanCode
                    shl     rax,56
                    or      r9,rax
                    mov     rcx,[rsi].Instance

                    [rcx].Post(edx, r8, r9)

                  .case MOUSE_EVENT

                    mov eax,[rdi].MouseEvent.dwMousePosition
                    mov r8d,[rdi].MouseEvent.dwControlKeyState
                    shl r8,32
                    or  r8,rax

                    mov ecx,[rsi].Buttons
                    mov eax,[rdi].MouseEvent.dwButtonState
                    xor edx,edx

                    .if ( eax != ecx )
                        .if ( ( ecx & FROM_LEFT_1ST_BUTTON_PRESSED ) && \
                             !( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONUP
                        .elseif ( !( ecx & FROM_LEFT_1ST_BUTTON_PRESSED ) && \
                                   ( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONDOWN
                        .elseif ( ( ecx & RIGHTMOST_BUTTON_PRESSED ) && \
                                 !( eax & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONUP
                        .elseif ( !( ecx & RIGHTMOST_BUTTON_PRESSED ) && \
                                   ( eax & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONDOWN
                        .endif
                        mov [rsi].Buttons,[rdi].MouseEvent.dwButtonState
                    .else
                        .switch pascal [rdi].MouseEvent.dwEventFlags
                          .case MOUSE_MOVED    : mov edx,WM_MOUSEMOVE
                          .case MOUSE_HWHEELED : mov edx,WM_MOUSEHWHEEL
                          .case MOUSE_WHEELED  : mov edx,WM_MOUSEWHEEL
                          .case DOUBLE_CLICK
                            .if ( eax == FROM_LEFT_1ST_BUTTON_PRESSED )
                                mov edx,WM_LBUTTONDBLCLK
                            .elseif ( eax == RIGHTMOST_BUTTON_PRESSED )
                                mov edx,WM_RBUTTONDBLCLK
                            .else
                                mov edx,WM_XBUTTONDBLCLK
                            .endif
                        .endsw
                    .endif
                    .if edx
                        mov rcx,[rsi].Instance
                        mov r9d,[rsi].Buttons
                        [rcx].Post(edx, r8, r9)
                    .endif

                  .case WINDOW_BUFFER_SIZE_EVENT
                    mov rcx,[rsi].Instance
                    [rcx].Post(WM_SIZE, 0, 0)
                  .case FOCUS_EVENT
                    mov [rsi].Focus,[rdi].FocusEvent.bSetFocus
                  .case MENU_EVENT
                    mov rcx,[rsi].Instance
                    [rcx].Post([rdi].MenuEvent.dwCommandId, 0, 0)
                .endsw
                dec EventCount
            .endw
        .endif

        assume rdi:nothing

        mov rcx,[rsi].Instance
        mov rdi,[rsi].Message

        .if ( rdi == NULL || [rsi].Focus == 0 )

            inc IdleCount
            .if IdleCount >= 100

                mov IdleCount,0
                [rcx].Send(WM_ENTERIDLE, 0, 0)
            .endif
            .continue
        .endif
        mov IdleCount,0

        .break .if ( [rdi].TMESSAGE.Message == WM_QUIT )

        Translate(rcx, rdi)
        Dispatch(rcx, rdi)
    .endw
    mov rbx,[rdi].TMESSAGE.wParam
    Dispatch(rcx, rdi)
    [rcx].Send(WM_CLOSE, 0, 0)
    mov rcx,hPrev
    mov [rsi].Instance,rcx
    mov rax,rbx
    ret

TWindow::Register endp

    end
